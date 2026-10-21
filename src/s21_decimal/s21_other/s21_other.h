#ifndef SRC_S21_DECIMAL_S21_OTHER_S21_OTHER_H
#define SRC_S21_DECIMAL_S21_OTHER_S21_OTHER_H

#include "../../s21_decimal.h"
#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "../s21_types.h"

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
void s21_decimal_null_service_bits(s21_decimal *value);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

// Declarations of functions

#endif  // SRC_S21_DECIMAL_S21_OTHER_S21_OTHER_H
