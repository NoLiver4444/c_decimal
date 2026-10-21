#ifndef SRC_S21_DECIMAL_S21_ARITHMETIC_S21_ARITHMETIC_H
#define SRC_S21_DECIMAL_S21_ARITHMETIC_S21_ARITHMETIC_H

#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "../s21_types.h"

// Результаты выполнения кода
typedef enum s21_arithmetic_result {
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_BIG = 1,
  S21_ARITHMETIC_SMALL = 2,
  S21_ARITHMETIC_ZERO_DIV = 3,
  S21_ARITHMETIC_ERROR = 4,
  TEST_ARITHMETIC_OK = 0,
  TEST_ARITHMETIC_BIG = 1,
  TEST_ARITHMETIC_ZERO_DIV = 3,
  TEST_ARITHMETIC_SMALL = 2
} s21_arithmetic_result;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_make(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_handle(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_make(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_make(s21_int_256 value_2_256, s21_int_256 res,
                 s21_int_256 remainder, s21_decimal *result);
int s21_div_calc_fractional(s21_int_256 *res, s21_int_256 value_2_256,
                            s21_int_256 *remainder);

#endif  // SRC_S21_DECIMAL_S21_ARITHMETIC_S21_ARITHMETIC_H
