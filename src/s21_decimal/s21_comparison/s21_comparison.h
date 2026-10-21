#ifndef SRC_S21_DECIMAL_S21_COMPARISON_S21_COMPARISON_H
#define SRC_S21_DECIMAL_S21_COMPARISON_S21_COMPARISON_H

#include "../s21_simple/simple_arnoldea/s21_simple_arnoldea.h"
#include "../s21_types.h"

// Declarations of functions
// s21_align_scales
void s21_align_scales(s21_decimal *value1, s21_decimal *value2);
void s21_multiply_by_ten(s21_decimal *dec);

// s21_is_equal
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

// s21_is_greater_or_equal
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// s21_is_greater
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

// s21_is_less_or_equal
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// s21_is_less
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_without_sign(s21_decimal value_1, s21_decimal value_2);

// s21_is_not_equal
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// s21_remove_trailing_zeros
void s21_remove_trailing_zeros_arnoldea(s21_decimal *dec);
int s21_divide_by_ten(s21_decimal *dec);

#endif  // SRC_S21_DECIMAL_S21_COMPARISON_S21_COMPARISON_H
