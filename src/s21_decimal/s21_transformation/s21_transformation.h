#ifndef SRC_S21_DECIMAL_S21_TRANSFORMATION_S21_TRANSFORMATION_H
#define SRC_S21_DECIMAL_S21_TRANSFORMATION_S21_TRANSFORMATION_H

#include <stdlib.h>

#include "../s21_types.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

typedef enum s21_conversion_result {
  S21_CONVERSION_OK = 0,
  S21_CONVERSION_ERROR = 1
} s21_conversion_result;

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

// Вспомогательные функции

s21_decimal s21_decimal_get_from_char(char c);
int s21_get_float_exp_from_string(char *str);
s21_decimal s21_float_string_to_decimal(char *str);
void s21_decimal_set_sign(s21_decimal *decimal, int sign);
void s21_decimal_div_by_10(s21_decimal *value);
int s21_decimal_get_scale(s21_decimal value);
#endif  // SRC_S21_DECIMAL_S21_TRANSFORMATION_S21_TRANSFORMATION_H
