#include "s21_simple_dickcart.h"

// Функция возвращает модуль value
s21_decimal s21_abs(s21_decimal value) {
  s21_decimal result = value;
  s21_set_sign(&result, S21_POSITIVE);
  return result;
}

// Фунгкция для сравнения value_1 и value_2
int s21_is_equal_dickcart(s21_decimal value_1, s21_decimal value_2) {
  // Удаляем нулевые знаки из значений
  s21_decimal tmp1 = s21_remove_trailing_zeros(value_1);
  s21_decimal tmp2 = s21_remove_trailing_zeros(value_2);

  int code = S21_COMPARISON_TRUE;

  // Проверяем, равны ли оба значения (включая знак и степень)
  if (tmp1.bits[0] == 0 && tmp1.bits[1] == 0 && tmp1.bits[2] == 0 &&
      tmp2.bits[0] == 0 && tmp2.bits[1] == 0 && tmp2.bits[2] == 0) {
    // Считаем -0 == 0, поэтому знаковый бит не проверяем, степени уже будут
    // равны после отбрасывания конечных нулей
    code = S21_COMPARISON_TRUE;
  } else {
    code = tmp1.bits[0] == tmp2.bits[0] && tmp1.bits[1] == tmp2.bits[1] &&
           tmp1.bits[2] == tmp2.bits[2] && tmp1.bits[3] == tmp2.bits[3];
  }
  // Если все блоки равны, возвращаем TRUE
  return code;
}

// Функция для нахождения максимального числа
int s21_max(int value_1, int value_2) {
  int result = value_2;
  if (value_1 > value_2) {
    result = value_1;
  }

  return result;
}

// Функция отбрасывает конечные 0 числа value
s21_decimal s21_remove_trailing_zeros(s21_decimal value) {
  s21_decimal result = value;
  int power = s21_decimal_get_power(value);
  int sign = s21_decimal_get_sign(value);

  if (power > 0 && s21_is_correct_decimal(value)) {
    s21_decimal remainder = s21_decimal_get_zero();
    s21_decimal tmp = value;
    s21_decimal_null_service_bits(&tmp);

    // Делим число на 10, уменьшая степень decimal, до тех пор, пока остаток от
    // деления равен нулю
    while (power > 0) {
      tmp = s21_int_128_binary_division(tmp, s21_int_128_get_ten_pow(1),
                                        &remainder);
      if (s21_int_128_binary_equal_zero(remainder)) {
        --power;
        result = tmp;
      } else {
        break;
      }
    }
    s21_decimal_set_power(&result, power);
    s21_set_sign(&result, sign);
  }

  return result;
}

// Функция для банковского округления
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
  s21_decimal zerofive = s21_decimal_get_zerofive();
  s21_decimal result;

  if (s21_is_equal_dickcart(fractional, zerofive)) {
    // Если дробная часть ровно 0.5
    if (s21_decimal_even(integral)) {
      // Если целая часть четная, то оставляем её
      result = integral;
    } else {
      // Если целая часть нечетная, то увеличиваем её на 1
      result = s21_int_128_binary_addition(integral, s21_decimal_get_one());
    }
  } else if (s21_is_greater_dickcart(fractional, zerofive)) {
    // Если дробная часть > 0.5, то увеличиваем целую часть на 1
    result = s21_int_128_binary_addition(integral, s21_decimal_get_one());
  } else {
    // Если дробная часть < 0.5, то оставляем целую часть без изменений
    result = integral;
  }

  return result;
}

// Функция для проверки что value_1 больше value_2
int s21_is_greater_dickcart(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less_dickcart(value_2, value_1);
}

// Функция для пероверки что value_1 меньше value_2
int s21_is_less_dickcart(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_result code = S21_COMPARISON_FALSE;

  int sign1 = s21_decimal_get_sign(value_1);
  int sign2 = s21_decimal_get_sign(value_2);

  if (s21_is_equal_dickcart(value_1, s21_decimal_get_zero()) &&
      s21_is_equal_dickcart(value_2, s21_decimal_get_zero())) {
    // Если оба 0, то всегда false
    code = S21_COMPARISON_FALSE;
  } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
    // Отрицательное число (value_1) всегда меньше положительного (value_2)
    code = S21_COMPARISON_TRUE;
  } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
    // Положительное число (value_1) всегда не меньше отрицательного (value_2)
    code = S21_COMPARISON_FALSE;
  } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
    // Отрицательные числа делаем положительными и сравниваем наоборот
    // Т.к. 2 < 3, но -2 > -3
    code = s21_is_less_handle(s21_abs(value_2), s21_abs(value_1));
  } else {
    // В остальных случаях просто сравниваем
    code = s21_is_less_handle(value_1, value_2);
  }

  return code;
}

// Функция для сравнения двух decimal (вспомогательная)
int s21_is_less_handle(s21_decimal value_1, s21_decimal value_2) {
  s21_comparison_result code = S21_COMPARISON_FALSE;
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;
  s21_int_256 tmp1l;
  s21_int_256 tmp2l;

  // Выравниваем степени слагаемых (знак и степень при этом будут обнулены)
  s21_decimal_leveling(tmp1, tmp2, &tmp1l, &tmp2l);

  // Сравниваем выравненные числа
  int compare = s21_int_256_binary_compare(tmp1l, tmp2l);

  if (compare == -1) {
    code = S21_COMPARISON_TRUE;
  } else {
    code = S21_COMPARISON_FALSE;
  }

  return code;
}

// Функция для проверки value_1 >= value_2
int s21_is_greater_or_equal_dickcart(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater_dickcart(value_1, value_2) ||
         s21_is_equal_dickcart(value_1, value_2);
}

int s21_negate_dickcart(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  if (!result) {
    // сли указатель на decimal является NULL
    code = S21_OTHER_ERROR;
  } else {
    // В остальных случаях меняем знак
    *result = value;
    s21_set_sign(result, !s21_decimal_get_sign(*result));

    if (!s21_is_correct_decimal(value)) {
      // Если value не является корректными decimal, то выставляем код ошибки
      code = S21_OTHER_ERROR;
    }
  }

  return code;
}
