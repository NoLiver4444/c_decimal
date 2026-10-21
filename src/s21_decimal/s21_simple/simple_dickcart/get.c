#include "s21_simple_dickcart.h"

// Функция для получения определённого бита
int s21_get_bit(const s21_decimal *value, int bit_index) {
  return (value->bits[bit_index / 32] >> (bit_index % 32)) & 1;
}

// Функция для нахождения степени 10
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
int s21_get_power(const s21_decimal *value) {
  return (value->bits[3] >> 16) & 0xFF;
}

/**
 * Retrieves the sign of a s21_decimal value.
 *
 * This function extracts the sign bit from the s21_decimal structure.
 * It returns 0 for positive values and 1 for negative values.
 *
 * @param value The s21_decimal value from which to retrieve the sign.
 * @return The sign of the s21_decimal value (0 for positive, 1 for negative).
 */
int s21_get_sign(const s21_decimal *value) {
  return ((unsigned int)value->bits[3] >> 31) & 1;
}
