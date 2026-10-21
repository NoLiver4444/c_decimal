#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "s21_other.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  if (!result) {
    code = S21_OTHER_ERROR;
  } else {
    *result = value;
    s21_set_sign(result, !s21_decimal_get_sign(*result));
  }

  return code;
}
