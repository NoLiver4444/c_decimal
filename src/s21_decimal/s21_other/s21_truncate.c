#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "s21_other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  if (!result) {
    // Если указатель на decimal является NULL
    code = S21_OTHER_ERROR;
  } else if (!s21_is_correct_decimal(value)) {
    // Проверяем, что value является корректными decimal
    code = S21_OTHER_ERROR;
    *result = s21_decimal_get_inf();
  } else {
    // В остальных случаях производим расчет
    *result = s21_decimal_get_zero();
    int power = s21_get_power(&value);
    s21_decimal tmp = value;
    s21_decimal_null_service_bits(&tmp);

    tmp =
        s21_int_128_binary_division(tmp, s21_int_128_get_ten_pow(power), NULL);

    *result = tmp;
    if (s21_decimal_get_sign(value) == S21_NEGATIVE) {
      s21_set_sign(result, S21_NEGATIVE);
    }
  }

  return code;
}
