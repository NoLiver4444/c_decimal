#include "s21_comparison.h"

/**
 * @brief Compares two s21_decimal numbers to determine if the first is greater
 * than the second.
 *
 * This function checks if the first s21_decimal number is greater than the
 * second by utilizing the s21_is_less function. It returns 1 if the first
 * number is greater than the second, and 0 otherwise.
 *
 * @param value_1 The first s21_decimal number to compare.
 * @param value_2 The second s21_decimal number to compare.
 * @return int 1 if value_1 is greater than value_2, 0 otherwise.
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}
