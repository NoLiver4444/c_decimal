#include "s21_simple_dickcart.h"

// Функция для бинарного сложения двоичных положительных чисел размера 128 бит
s21_decimal s21_int_128_binary_addition(s21_decimal decimal_1,
                                        s21_decimal decimal_2) {
  s21_decimal result = decimal_1;
  s21_decimal tmp = decimal_2;
  // Сложение выполняется с помощью and и xor
  while (!s21_int_128_binary_equal_zero(tmp)) {
    s21_decimal overflow_bits = s21_int_128_binary_and(result, tmp);
    overflow_bits = s21_int_128_binary_shift_left(overflow_bits, 1);
    result = s21_int_128_binary_xor(result, tmp);
    tmp = overflow_bits;
  }

  return result;
}

// Функция делает побитовое and
s21_decimal s21_int_128_binary_and(s21_decimal decimal_1,
                                   s21_decimal decimal_2) {
  s21_decimal result = s21_decimal_get_zero();

  // Побитовое ans для всех битов в массиве
  for (int i = 0; i < 4; i++) {
    result.bits[i] = decimal_1.bits[i] & decimal_2.bits[i];
  }

  return result;
}

// Функция побитова сравнивает decimal_1 и decimal_2
int s21_int_128_binary_compare(s21_decimal decimal_1, s21_decimal decimal_2) {
  int result = 0;

  for (int i = MAX_BITS - 1; i >= 0; --i) {
    int b1 = s21_decimal_is_set_bit(decimal_1, i);
    int b2 = s21_decimal_is_set_bit(decimal_2, i);

    if (b1 == 0 && b2 != 0) {
      result = -1;
    } else if (b1 != 0 && b2 == 0) {
      result = 1;
    }

    if (result != 0) {
      break;
    }
  }

  return result;
}

// Функция для бинарного деления
// Деление реализуется методом c восстановлением остатка
s21_decimal s21_int_128_binary_division(s21_decimal decimal_1,
                                        s21_decimal decimal_2,
                                        s21_decimal *remainder) {
  s21_decimal result;

  // Частичный остаток при расчетах
  s21_decimal partial_remainder = s21_decimal_get_zero();

  // Частное
  s21_decimal quotient = s21_decimal_get_zero();

  if (s21_int_128_binary_equal_zero(decimal_1)) {
    // Когда делимое равно 0
    quotient = s21_decimal_get_zero();
    partial_remainder = s21_decimal_get_zero();
  } else if (s21_int_128_binary_compare(decimal_1, decimal_2) == -1) {
    // Когда делимое меньше делителя
    quotient = s21_decimal_get_zero();
    partial_remainder = decimal_1;
  } else {
    // Деление чисел методом без восстановления остатка.

    // Рассчитываем предварительный сдвиг делителя
    int left1 = s21_decimal_get_not_zero_bit(decimal_1);
    int left2 = s21_decimal_get_not_zero_bit(decimal_2);
    int shift = left1 - left2;

    s21_decimal shifted_divisor =
        s21_int_128_binary_shift_left(decimal_2, shift);
    s21_decimal dividend = decimal_1;

    int need_subtraction = 1;

    // Повторяем действия k+1 раз
    while (shift >= 0) {
      // Определяем какое дейтсвие нужно сделать
      if (need_subtraction == 1) {
        partial_remainder =
            s21_int_128_binary_subtraction(dividend, shifted_divisor);
      } else {
        partial_remainder =
            s21_int_128_binary_addition(dividend, shifted_divisor);
      }

      // Сдвигаем влево на 1 частное и записываем в младший бит результата 1,
      // если старший бит частичного остатка равен 1
      quotient = s21_int_128_binary_shift_left(quotient, 1);
      if (!s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1)) {
        quotient = s21_decimal_set_bit(quotient, 0);
      }

      dividend = s21_int_128_binary_shift_left(partial_remainder, 1);

      // Если старший бит частичного остатка равен 0, то на следующей итерации
      // необходимо проводить вычитание
      if (!s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1)) {
        need_subtraction = 1;
      } else {
        need_subtraction = 0;
      }
      --shift;
    }
    // Проверяем остаток
    if (s21_decimal_is_set_bit(partial_remainder, MAX_BITS - 1)) {
      partial_remainder =
          s21_int_128_binary_addition(partial_remainder, shifted_divisor);
    }
    // Частичный остаток
    partial_remainder =
        s21_int_128_binary_shift_right(partial_remainder, left1 - left2);
  }

  // Заполняем переменные результата
  result = quotient;
  if (remainder != NULL) {
    *remainder = partial_remainder;
  }

  return result;
}

// Функция для сравнивания decimal с 0
int s21_int_128_binary_equal_zero(s21_decimal decimal) {
  return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 &&
         decimal.bits[3] == 0;
}

// Функция для бинарного умножения чисел
s21_int_256 s21_int_128_binary_multiplication(s21_decimal decimal_1,
                                              s21_decimal decimal_2) {
  s21_int_256 int_256_result =
      s21_create_int_256_from_decimal(s21_decimal_get_zero());
  s21_int_256 int_256_tmp = s21_create_int_256_from_decimal(decimal_1);

  int max_bit = s21_decimal_get_not_zero_bit(decimal_2);

  for (int i = 0; i <= max_bit; ++i) {
    if (s21_decimal_is_set_bit(decimal_2, i) != 0) {
      int_256_result = s21_int_256_binary_addition(int_256_result, int_256_tmp);
    }

    int_256_tmp = s21_int_256_binary_shift_left(int_256_tmp, 1);
  }
  return int_256_result;
}

// Побитовая инверсия
s21_decimal s21_int_128_binary_not(s21_decimal decimal) {
  s21_decimal result = s21_decimal_get_zero();
  result.bits[0] = ~decimal.bits[0];
  result.bits[1] = ~decimal.bits[1];
  result.bits[2] = ~decimal.bits[2];
  result.bits[3] = ~decimal.bits[3];

  return result;
}

// Функция для битового сдвига влево на один для чисел decimal
s21_decimal s21_int_128_binary_shift_left_one(s21_decimal decimal) {
  s21_decimal result = s21_decimal_get_zero();

  int b0 = s21_is_set_bit(decimal.bits[0], MAX_BLOCK_BITS - 1);
  unsigned int result0 = decimal.bits[0];
  result0 = result0 << 1;
  result.bits[0] = result0;

  int b1 = s21_is_set_bit(decimal.bits[1], MAX_BLOCK_BITS - 1);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 << 1;
  result.bits[1] = result1;

  int b2 = s21_is_set_bit(decimal.bits[2], MAX_BLOCK_BITS - 1);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 << 1;
  result.bits[2] = result2;

  unsigned int result3 = decimal.bits[3];
  result3 = result3 << 1;
  result.bits[3] = result3;

  if (b0) {
    result.bits[1] = s21_set_bit_2(result.bits[1], 0);
  }

  if (b1) {
    result.bits[2] = s21_set_bit_2(result.bits[2], 0);
  }

  if (b2) {
    result.bits[3] = s21_set_bit_2(result.bits[3], 0);
  }

  return result;
}

// Функция для битового сдвига влево для чисел типа decimal
s21_decimal s21_int_128_binary_shift_left(s21_decimal decimal, int shift) {
  s21_decimal result = decimal;
  while (shift > 0) {
    result = s21_int_128_binary_shift_left_one(result);
    --shift;
  }

  return result;
}

// Функция для битового сдвига вправо на один для чисел decimal
s21_decimal s21_int_128_binary_shift_right_one(s21_decimal decimal) {
  s21_decimal result = s21_decimal_get_zero();

  int b3 = s21_is_set_bit(decimal.bits[3], 0);
  unsigned int result3 = decimal.bits[3];
  result3 = result3 >> 1;
  result.bits[3] = result3;

  int b2 = s21_is_set_bit(decimal.bits[2], 0);
  unsigned int result2 = decimal.bits[2];
  result2 = result2 >> 1;
  result.bits[2] = result2;

  int b1 = s21_is_set_bit(decimal.bits[1], 0);
  unsigned int result1 = decimal.bits[1];
  result1 = result1 >> 1;
  result.bits[1] = result1;

  unsigned int result0 = decimal.bits[0];
  result0 = result0 >> 1;
  result.bits[0] = result0;

  if (b3) {
    result.bits[2] = s21_set_bit_2(result.bits[2], MAX_BLOCK_BITS - 1);
  }

  if (b2) {
    result.bits[1] = s21_set_bit_2(result.bits[1], MAX_BLOCK_BITS - 1);
  }

  if (b1) {
    result.bits[0] = s21_set_bit_2(result.bits[0], MAX_BLOCK_BITS - 1);
  }

  return result;
}

// Функция для битового сдвига вправо для чисел типа decimal
s21_decimal s21_int_128_binary_shift_right(s21_decimal decimal, int shift) {
  s21_decimal result = decimal;
  while (shift > 0) {
    result = s21_int_128_binary_shift_right_one(result);
    --shift;
  }

  return result;
}

// Функция для бинарного вычитания
s21_decimal s21_int_128_binary_subtraction(s21_decimal decimal1,
                                           s21_decimal decimal2) {
  s21_decimal result;
  decimal2 = s21_int_128_binary_not(decimal2);
  decimal2 = s21_int_128_binary_addition(decimal2, s21_decimal_get_one());
  result = s21_int_128_binary_addition(decimal1, decimal2);

  return result;
}

// Функция делает xor для decimal
s21_decimal s21_int_128_binary_xor(s21_decimal decimal_1,
                                   s21_decimal decimal_2) {
  s21_decimal result = s21_decimal_get_zero();

  for (int i = 0; i < 4; ++i) {
    result.bits[i] = decimal_1.bits[i] ^ decimal_2.bits[i];
  }

  return result;
}

// Функция для получения 10 в степени pow вида decimal
s21_decimal s21_int_128_get_ten_pow(int power) { return all_ten_pows[power]; }

s21_decimal s21_int128_get_ten_pow(int pow) { return all_ten_pows[pow]; }
