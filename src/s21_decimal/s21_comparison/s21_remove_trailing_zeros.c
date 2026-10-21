#include "s21_comparison.h"

/**
 * @brief Removes trailing zeros from a s21_decimal number.
 *
 * This function reduces the scale of a s21_decimal number by removing trailing
 * zeros. It repeatedly divides the number by ten until no more trailing zeros
 * can be removed, adjusting the scale accordingly.
 *
 * @param dec Pointer to the s21_decimal number from which trailing zeros will
 * be removed.
 */
void s21_remove_trailing_zeros_arnoldea(s21_decimal *dec) {
  int scale = (dec->bits[3] >> 16) & 0xFF;
  while (scale > 0 && s21_divide_by_ten(dec)) {
    scale--;
  }
  dec->bits[3] = (dec->bits[3] & 0xFF00FFFF) | (scale << 16);
}

/**
 * @brief Divides a s21_decimal number by ten.
 *
 * This function divides a s21_decimal number by ten and returns whether the
 * division resulted in a remainder of zero. It updates the number in place.
 *
 * @param dec Pointer to the s21_decimal number to be divided by ten.
 * @return 1 if the division resulted in no remainder, 0 otherwise.
 */
int s21_divide_by_ten(s21_decimal *dec) {
  s21_decimal result = {{0, 0, 0, 0}};
  unsigned long long remainder = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long current = (remainder << 32) | dec->bits[i];
    result.bits[i] = current / 10;
    remainder = current % 10;
  }

  *dec = result;
  return (remainder == 0);
}
