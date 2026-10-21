#include "s21_comparison.h"

/**
 * @brief Compares two s21_decimal numbers to determine if the first is greater
 * than or equal to the second.
 *
 * This function checks if the first s21_decimal number is either equal to or
 * greater than the second by utilizing the s21_is_equal and s21_is_greater
 * functions. It returns 1 if the first number is greater than or equal to the
 * second, and 0 otherwise.
 *
 * @param value_1 The first s21_decimal number to compare.
 * @param value_2 The second s21_decimal number to compare.
 * @return int 1 if value_1 is greater than or equal to value_2, 0 otherwise.
 */
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_greater(value_1, value_2);
}
