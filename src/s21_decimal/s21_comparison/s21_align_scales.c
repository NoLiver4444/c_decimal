#include "s21_comparison.h"

/**
 * @brief Aligns the scales of two s21_decimal numbers.
 *
 * This function adjusts the scales of two s21_decimal numbers so that they are
 * equal. If the scale of the first number is greater than the second, the
 * second number is multiplied by ten until its scale matches the first.
 * Conversely, if the scale of the second number is greater, the first number is
 * multiplied by ten until its scale matches the second. The scale is stored in
 * the higher bits of the fourth element of the bits array.
 *
 * @param dec1 Pointer to the first s21_decimal number.
 * @param dec2 Pointer to the second s21_decimal number.
 * @author arnoldea
 */
void s21_align_scales(s21_decimal *dec1, s21_decimal *dec2) {
  int sign_1 = s21_get_sign_arnoldea(dec1);
  int sign_2 = s21_get_sign_arnoldea(dec2);

  int scale1 = (dec1->bits[3] >> 16) & 0xFF;
  int scale2 = (dec2->bits[3] >> 16) & 0xFF;

  if (scale1 > scale2) {
    // Увеличиваем масштаб второго числа
    int scale_diff = scale1 - scale2;
    for (int i = 0; i < scale_diff; i++) {
      s21_multiply_by_ten(dec2);
    }
    dec2->bits[3] = (dec2->bits[3] & 0xFF00FFFF) | (scale1 << 16);

  } else if (scale2 > scale1) {
    // Увеличиваем масштаб первого числа
    int scale_diff = scale2 - scale1;
    for (int i = 0; i < scale_diff; i++) {
      s21_multiply_by_ten(dec1);
    }
    dec1->bits[3] = (dec1->bits[3] & 0xFF00FFFF) | (scale2 << 16);
  }

  s21_set_sign_arnoldea(dec1, sign_1);
  s21_set_sign_arnoldea(dec2, sign_2);
}

/**
 * @brief Multiplies a s21_decimal number by ten.
 *
 * This function takes a pointer to a s21_decimal number and multiplies it by
 * ten. The multiplication is performed in a way that handles potential overflow
 * by using a temporary variable to store the original value and a result
 * variable to accumulate the final result.
 *
 * @param dec Pointer to the s21_decimal number to be multiplied.
 * @author arnoldea
 */
void s21_multiply_by_ten(s21_decimal *dec) {
  s21_decimal temp = *dec;
  s21_decimal result = {{0, 0, 0, 0}};

  // Умножение на 10
  for (int i = 0; i < 3; i++) {
    unsigned long long part = (unsigned long long)temp.bits[i] * 10;
    result.bits[i] = part & 0xFFFFFFFF;
    if (i < 2) {
      result.bits[i + 1] += part >> 32;
    }
  }

  *dec = result;
}
