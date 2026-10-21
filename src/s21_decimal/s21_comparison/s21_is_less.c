#include "s21_comparison.h"

/**
 * @brief Compares two s21_decimal numbers to determine if the first is less
 * than the second.
 *
 * This function evaluates two s21_decimal numbers, taking into account their
 * signs. It returns 1 if the first number is less than the second, and 0
 * otherwise. If both numbers are zero, it returns 0. The function handles cases
 * where the signs of the numbers differ, as well as when both numbers are
 * negative, by using the s21_is_less_without_sign function for absolute value
 * comparison.
 *
 * @param value_1 The first s21_decimal number.
 * @param value_2 The second s21_decimal number.
 * @return int 1 if value_1 is less than value_2, 0 otherwise.
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  int sign_1 = s21_get_sign_arnoldea(&value_1);
  int sign_2 = s21_get_sign_arnoldea(&value_2);

  s21_decimal temp_1 = value_1;
  s21_decimal temp_2 = value_2;

  if (temp_1.bits[0] == 0 && temp_1.bits[1] == 0 && temp_1.bits[2] == 0 &&
      temp_2.bits[0] == 0 && temp_2.bits[1] == 0 && temp_2.bits[2] == 0) {
    result = 0;

  } else if (sign_1 == 1 && sign_2 == 0) {
    result = 1;

  } else if (sign_1 == 0 && sign_2 == 1) {
    result = 0;

  } else if (sign_1 == 1 && sign_2 == 1) {
    result = s21_is_less_without_sign(temp_2, temp_1);

  } else {
    result = s21_is_less_without_sign(temp_1, temp_2);
  }

  return result;
}

/**
 * @brief Compares two s21_decimal numbers without considering their sign to
 * determine if the first is less than the second.
 *
 * This function compares two s21_decimal numbers without considering their sign
 * and returns 1 if the first number is less than the second, and 0 otherwise.
 * The comparison takes into account the scale of the numbers.
 *
 * @param value_1 The first s21_decimal number.
 * @param value_2 The second s21_decimal number.
 * @return int 1 if the absolute value of value_1 is less than the absolute
 * value of value_2, 0 otherwise.
 */
int s21_is_less_without_sign(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  s21_decimal temp_1 = value_1;
  s21_decimal temp_2 = value_2;

  s21_align_scales(&temp_1, &temp_2);

  int flag = 0;
  for (int i = 2; i >= 0 && flag == 0; i--) {
    for (int j = 31; j >= 0 && flag == 0; j--) {
      int bit1 = (temp_1.bits[i] >> j) & 1;
      int bit2 = (temp_2.bits[i] >> j) & 1;
      if (bit1 < bit2) {
        result = 1;
        flag = 1;
      } else if (bit1 > bit2) {
        result = 0;
        flag = 1;
      }
    }
  }

  return result;
}
