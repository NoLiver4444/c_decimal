#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "s21_other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  if (!result) {
    // Если указатель на decimal является NULL
    code = S21_OTHER_ERROR;
  } else if (!s21_is_correct_decimal(value)) {
    // Проверяем, что value является корректными decimal
    code = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else {
    // В остальных случаях округляем
    *result = s21_decimal_get_zero();
    int sign = s21_decimal_get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    // Убираем знак
    s21_decimal value_unsigned = s21_abs(value);
    // Убираем дробную часть числа
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    // Считаем убранную дробную часть числа
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);

    // Производим округление, исходя из дробной части числа
    value_unsigned_truncated =
        s21_round_banking(value_unsigned_truncated, fractional);

    *result = value_unsigned_truncated;
    // Возвращаем знак
    s21_set_sign(result, sign);
  }

  return code;
}
