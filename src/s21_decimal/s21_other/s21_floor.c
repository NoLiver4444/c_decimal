#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "s21_other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;  // Проверка на NULL указатель

  // Инициализация результата
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  int sign = s21_get_sign(&value);
  s21_decimal value_unsigned = value;
  s21_decimal_null_service_bits(&value_unsigned);  // Очищаем служебные биты

  s21_decimal value_truncated;
  s21_truncate(value, &value_truncated);

  s21_decimal fractional;
  s21_sub(value_unsigned, value_truncated, &fractional);

  if (sign == S21_NEGATIVE &&
      !s21_is_equal(fractional, s21_decimal_get_zero())) {
    s21_sub(value_truncated, s21_decimal_get_one(), &value_truncated);
  }

  *result = value_truncated;
  if (sign == S21_NEGATIVE) {
    s21_set_sign(result, S21_NEGATIVE);
  }
  return 0;
}
