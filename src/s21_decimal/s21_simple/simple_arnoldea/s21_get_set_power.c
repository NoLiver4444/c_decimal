#include "s21_simple_arnoldea.h"

/**
 * @brief Retrieves the power of a given s21_decimal value.
 *
 * This function extracts the power stored in the higher bits of the
 * s21_decimal structure. The power is represented by the bits 16 to 23
 * of the third element of the bits array.
 *
 * @param value A pointer to the s21_decimal value from which to retrieve the
 * power.
 * @return The power of the s21_decimal value as an integer.
 */
int s21_get_power_arnoldea(const s21_decimal *value) {
  return (value->bits[3] >> 16) & 0xFF;
}

/**
 * @brief Sets the power of a given s21_decimal value.
 *
 * This function updates the power stored in the higher bits of the
 * s21_decimal structure. The power is represented by the bits 16 to 23
 * of the third element of the bits array.
 *
 * @param value A pointer to the s21_decimal value to which the power will be
 * set.
 * @param power The power to set, which will be stored in the s21_decimal value.
 */
void s21_set_power_arnoldea(s21_decimal *value, int power) {
  value->bits[3] |= (power & 0xFF) << 16;
}
