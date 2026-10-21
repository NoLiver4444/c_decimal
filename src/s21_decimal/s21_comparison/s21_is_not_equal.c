#include "s21_comparison.h"

/**
 * @brief Compares two s21_decimal values for inequality.
 *
 * This function takes two s21_decimal values and compares them for inequality.
 * If the values are not equal, it returns 1, otherwise it returns 0.
 *
 * @param value_1 The first s21_decimal value to compare.
 * @param value_2 The second s21_decimal value to compare.
 * @return 1 if the values are not equal, 0 otherwise.
 * @author arnoldea
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
