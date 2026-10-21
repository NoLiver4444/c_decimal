#include "s21_simple_arnoldea.h"

/**
 * Retrieves the sign of a s21_decimal value.
 *
 * This function extracts the sign bit from the s21_decimal structure.
 * It returns 0 for positive values and 1 for negative values.
 *
 * @param value The s21_decimal value from which to retrieve the sign.
 * @return The sign of the s21_decimal value (0 for positive, 1 for negative).
 */
int s21_get_sign_arnoldea(const s21_decimal *value) {
  return ((unsigned int)value->bits[3] >> 31) & 1;
}

/**
 * Sets the sign of a s21_decimal value.
 *
 * This function modifies the sign bit of the s21_decimal value.
 *
 * @param value The s21_decimal value to be modified.
 * @param sign The new sign value (0 for positive, 1 for negative).
 */
void s21_set_sign_arnoldea(s21_decimal *value, int sign) {
  value->bits[3] = (value->bits[3] & ~(1U << 31)) | (unsigned int)sign << 31;
}
