#include "s21_simple_arnoldea.h"

/**
 * @brief Retrieves the value of a specific bit from a s21_decimal structure.
 *
 * This function takes a pointer to a s21_decimal value and an index of the bit
 * to be retrieved. It calculates the appropriate word and bit position to
 * return the value of the specified bit (0 or 1).
 *
 * @param value Pointer to the s21_decimal structure from which to retrieve the
 * bit.
 * @param bit_index The index of the bit to retrieve (0-127).
 * @return The value of the specified bit (0 or 1).
 */
int s21_get_bit_arnoldea(const s21_decimal *value, int bit_index) {
  return (value->bits[bit_index / 32] >> (bit_index % 32)) & 1;
}

/**
 * @brief Sets the value of a specific bit in a s21_decimal structure.
 *
 * This function modifies the specified bit in the s21_decimal value
 * to the given bit_value (0 or 1). It calculates the appropriate word
 * and bit position to set the value of the specified bit.
 *
 * @param value Pointer to the s21_decimal structure in which to set the bit.
 * @param bit_index The index of the bit to set (0-127).
 * @param bit_value The value to set the bit to (0 or 1).
 */
void s21_set_bit_arnoldea(s21_decimal *value, int bit_index, int bit_value) {
  if (bit_value == 0) {
    value->bits[bit_index / 32] &= ~(1U << (bit_index % 32));
  } else {
    value->bits[bit_index / 32] |= 1U << (bit_index % 32);
  }
}
