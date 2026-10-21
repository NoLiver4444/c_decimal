#include "s21_simple_dickcart.h"

// Функция для создания большого числа
s21_int_256 s21_create_int_256_from_decimal(s21_decimal value_1) {
  s21_int_256 result;

  // В первый decimal записываем value
  result.decimal[0] = value_1;

  // Второй заполняем 0
  result.decimal[1] = s21_decimal_get_zero();

  return result;
}

// Функция для бинарного сложения двоичных положительных чисел размера 256 бит
s21_int_256 s21_int_256_binary_addition(s21_int_256 decimal_1,
                                        s21_int_256 decimal_2) {
  s21_int_256 result = decimal_1;
  s21_int_256 tmp = decimal_2;

  // Пока все элементы массивов bits не равны 0
  while (!s21_int_128_binary_equal_zero(tmp.decimal[0]) ||
         !s21_int_128_binary_equal_zero(tmp.decimal[1])) {
    s21_int_256 overflow_bits;

    overflow_bits.decimal[0] =
        s21_int_128_binary_and(result.decimal[0], tmp.decimal[0]);
    overflow_bits.decimal[1] =
        s21_int_128_binary_and(result.decimal[1], tmp.decimal[1]);

    overflow_bits = s21_int_256_binary_shift_left(overflow_bits, 1);
    result.decimal[0] =
        s21_int_128_binary_xor(result.decimal[0], tmp.decimal[0]);
    result.decimal[1] =
        s21_int_128_binary_xor(result.decimal[1], tmp.decimal[1]);

    tmp = overflow_bits;
  }

  return result;
}

// Функция для бинарного деления
// Деление реализуется методом c восстановлением остатка
s21_int_256 s21_int_256_binary_division(s21_int_256 decimal_1,
                                        s21_int_256 decimal_2,
                                        s21_int_256 *remainder) {
  s21_int_256 result;

  // Частичный остаток при расчетах
  s21_int_256 partial_remainder =
      s21_create_int_256_from_decimal(s21_decimal_get_zero());

  // Частное
  s21_int_256 quotient =
      s21_create_int_256_from_decimal(s21_decimal_get_zero());

  if (s21_int_128_binary_equal_zero(decimal_1.decimal[0]) &&
      s21_int_128_binary_equal_zero(decimal_1.decimal[1])) {
    // Когда делимое равно 0
    quotient = s21_create_int_256_from_decimal(s21_decimal_get_zero());
    partial_remainder = s21_create_int_256_from_decimal(s21_decimal_get_zero());
  } else if (s21_int_256_binary_compare(decimal_1, decimal_2) == -1) {
    // Когда делимое меньше делителя
    quotient = s21_create_int_256_from_decimal(s21_decimal_get_zero());
    partial_remainder = decimal_1;
  } else {
    // Деление чисел методом без восстановления остатка.

    // Рассчитываем предварительный сдвиг делителя
    int left1 = s21_decimal_get_not_zero_bit(decimal_1.decimal[1]);
    if (left1 == -1) {
      left1 = s21_decimal_get_not_zero_bit(decimal_1.decimal[0]);
    } else {
      left1 = MAX_BITS + left1;
    }

    int left2 = s21_decimal_get_not_zero_bit(decimal_2.decimal[1]);
    if (left2 == -1) {
      left2 = s21_decimal_get_not_zero_bit(decimal_2.decimal[0]);
    } else {
      left2 = MAX_BITS + left2;
    }

    int shift = left1 - left2;

    s21_int_256 shifted_divisor =
        s21_int_256_binary_shift_left(decimal_2, shift);
    s21_int_256 dividend = decimal_1;

    int need_subtraction = 1;

    // Повторяем действия k+1 раз
    while (shift >= 0) {
      // Определяем какое дейтсвие нужно сделать
      if (need_subtraction == 1) {
        partial_remainder =
            s21_int_256_binary_subtraction(dividend, shifted_divisor);
      } else {
        partial_remainder =
            s21_int_256_binary_addition(dividend, shifted_divisor);
      }

      // Сдвигаем влево на 1 частное и записываем в младший бит результата 1,
      // если старший бит частичного остатка равен 1
      quotient = s21_int_256_binary_shift_left(quotient, 1);
      if (s21_decimal_is_set_bit(partial_remainder.decimal[1], MAX_BITS - 1) ==
          0) {
        quotient.decimal[0] = s21_decimal_set_bit(quotient.decimal[0], 0);
      }

      dividend = s21_int_256_binary_shift_left(partial_remainder, 1);

      // Если старший бит частичного остатка равен 0, то на следующей итерации
      // необходимо проводить вычитание (Шаг 5 алгоритма)
      if (s21_decimal_is_set_bit(partial_remainder.decimal[1], MAX_BITS - 1) ==
          0) {
        need_subtraction = 1;
      } else {
        need_subtraction = 0;
      }
      --shift;
    }
    // Проверяем остаток
    if (s21_decimal_is_set_bit(partial_remainder.decimal[1], MAX_BITS - 1)) {
      partial_remainder =
          s21_int_256_binary_addition(partial_remainder, shifted_divisor);
    }
    // Частичный остаток
    partial_remainder =
        s21_int_256_binary_shift_right(partial_remainder, left1 - left2);
  }

  // Заполняем переменные результата
  result = quotient;
  if (remainder != NULL) {
    *remainder = partial_remainder;
  }

  return result;
}

// Функция для битового сдвига влево для чисел типа int_256
s21_int_256 s21_int_256_binary_shift_left(s21_int_256 decimal, int shift) {
  s21_int_256 result = decimal;

  while (shift > 0) {
    int b0 = s21_decimal_is_set_bit(result.decimal[0], MAX_BITS - 1);
    result.decimal[0] = s21_int_128_binary_shift_left_one(result.decimal[0]);
    result.decimal[1] = s21_int_128_binary_shift_left_one(result.decimal[1]);
    if (b0) {
      result.decimal[1] = s21_decimal_set_bit(result.decimal[1], 0);
    }
    --shift;
  }

  return result;
}

// Функция для битового сдвига вправо для чисел типа int_256
s21_int_256 s21_int_256_binary_shift_right(s21_int_256 decimal, int shift) {
  s21_int_256 result = decimal;
  while (shift > 0) {
    int b1 = s21_decimal_is_set_bit(result.decimal[1], 0);
    result.decimal[0] = s21_int_128_binary_shift_right_one(result.decimal[0]);
    result.decimal[1] = s21_int_128_binary_shift_right_one(result.decimal[1]);
    if (b1) {
      result.decimal[0] = s21_decimal_set_bit(result.decimal[0], MAX_BITS - 1);
    }
    --shift;
  }

  return result;
}

// Функция для бинарного вычитания двоичных положительных целых чисел размера
// 256 бит Делаем через сложение
s21_int_256 s21_int_256_binary_subtraction(s21_int_256 decimal_1,
                                           s21_int_256 decimal_2) {
  s21_int_256 result;

  // Переделываем decimal_2 в обратный код
  decimal_2.decimal[0] = s21_int_128_binary_not(decimal_2.decimal[0]);
  decimal_2.decimal[1] = s21_int_128_binary_not(decimal_2.decimal[1]);

  s21_int_256 one = s21_create_int_256_from_decimal(s21_decimal_get_one());

  // Складываем decimal_1 и (decimal_2 + 1)
  decimal_2 = s21_int_256_binary_addition(decimal_2, one);
  result = s21_int_256_binary_addition(decimal_1, decimal_2);

  return result;
}

// Функция которая находит сколько раз необходимо разделить 256 битный int на
// 10, чтобы результат поместился в 96 битный int
int s21_int_256_get_shift_to_decimal(s21_int_256 value) {
  int cnt = 0;

  // Если value содержит только нули, то расчет не производим, резльтат - 0
  if (!(s21_int_128_binary_equal_zero(value.decimal[0]) &&
        s21_int_128_binary_equal_zero(value.decimal[1]))) {
    // Максимальное 96 битное число
    s21_int_256 max = s21_create_int_256_from_decimal(s21_decimal_get_max());

    // Находим число, во сколько раз value больше максимального 96 битного числа
    s21_int_256 quotient = s21_int_256_binary_division(value, max, NULL);

    // Перебираем все степени 10, чтобы найти ближайшую большую степень, чем
    // quotient
    while (1) {
      int compare = s21_int_128_binary_compare(quotient.decimal[0],
                                               s21_int_128_get_ten_pow(cnt));
      if (compare == -1 || compare == 0) {
        break;
      }
      ++cnt;
    }

    // Проверяем, что value впишется в 96 бит, если поделить на 10 в найденной
    // степени
    s21_int_256 tmp = s21_int_256_binary_division(
        value, s21_create_int_256_from_decimal(s21_int_128_get_ten_pow(cnt)),
        NULL);
    // Если не помещается, то берем следующую степень
    if (!s21_int_128_binary_equal_zero(tmp.decimal[1]) ||
        tmp.decimal[0].bits[3] != 0) {
      ++cnt;
    }
  }

  return cnt;
}

// Функция для сравнения двуч 256 битных числа
int s21_int_256_binary_compare(s21_int_256 decimal_1, s21_int_256 decimal_2) {
  int compare =
      s21_int_128_binary_compare(decimal_1.decimal[1], decimal_2.decimal[1]);

  if (compare == 0) {
    compare =
        s21_int_128_binary_compare(decimal_1.decimal[0], decimal_2.decimal[0]);
  }

  return compare;
}

// Фугкция для бинарного умножения 256 битных чисел
s21_int_256 s21_int_256_binary_multiplication(s21_int_256 decimal_1,
                                              s21_decimal decimal_2) {
  s21_int_256 int_256_result =
      s21_create_int_256_from_decimal(s21_decimal_get_zero());
  s21_int_256 int_256_tmp1 = decimal_1;

  int max_bit = s21_decimal_get_not_zero_bit(decimal_2);

  for (int i = 0; i <= max_bit; i++) {
    if (s21_decimal_is_set_bit(decimal_2, i) != 0) {
      int_256_result =
          s21_int_256_binary_addition(int_256_result, int_256_tmp1);
    }

    int_256_tmp1 = s21_int_256_binary_shift_left(int_256_tmp1, 1);
  }

  return int_256_result;
}
