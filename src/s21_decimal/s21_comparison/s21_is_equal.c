#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"
#include "s21_comparison.h"

/**
 * @brief Compares two s21_decimal values for equality.
 *
 * This function takes two s21_decimal values and compares them for equality.
 * If the values are equal, it returns 1, otherwise it returns 0.
 *
 * @param value_1 The first s21_decimal value to compare.
 * @param value_2 The second s21_decimal value to compare.
 * @return 1 if the values are equal, 0 otherwise.
 * @author arnoldea
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  s21_decimal temp_1 = value_1;
  s21_decimal temp_2 = value_2;

  // Выравнивание чисел по масштабу
  temp_1 = s21_remove_trailing_zeros(temp_1);
  temp_2 = s21_remove_trailing_zeros(temp_2);

  if (temp_1.bits[0] == 0 && temp_1.bits[1] == 0 && temp_1.bits[2] == 0 &&
      temp_2.bits[0] == 0 && temp_2.bits[1] == 0 && temp_2.bits[2] == 0) {
    result = 1;
  } else {
    if (temp_1.bits[0] == temp_2.bits[0] && temp_1.bits[1] == temp_2.bits[1] &&
        temp_1.bits[2] == temp_2.bits[2] && temp_1.bits[3] == temp_2.bits[3]) {
      result = 1;
    } else {
      result = 0;
    }
  }

  return result;
}
