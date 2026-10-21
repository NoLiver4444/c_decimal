#include "s21_simple_dickcart.h"

// Функция для проверка установлен ли в числе number бит index
int s21_is_set_bit(int number, int index) { return !!(number & (1U << index)); }

// Функция устанавливает бит index в числе number 1
void s21_set_bit(s21_decimal *value, int bit_index, int bit_value) {
  if (bit_value == 1) {
    value->bits[bit_index / 32] &= ~(1U << (bit_index % 32));
  } else {
    value->bits[bit_index / 32] |= 1U << (bit_index % 32);
  }
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
void s21_set_power(s21_decimal *value, int power) {
  value->bits[3] |= (power & 0xFF) << 16;
}
void s21_decimal_set_power(s21_decimal *decimal, int power) {
  decimal_bit3 bits3;
  bits3.i = decimal->bits[3];
  bits3.parts.power = power;

  decimal->bits[3] = bits3.i;
}

/**
 * Sets the sign of a s21_decimal value.
 *
 * This function modifies the sign bit of the s21_decimal value.
 *
 * @param value The s21_decimal value to be modified.
 * @param sign The new sign value (0 for positive, 1 for negative).
 */
void s21_set_sign(s21_decimal *value, int sign) {
  value->bits[3] = (value->bits[3] & ~(1U << 31)) | (unsigned int)sign << 31;
}

int s21_set_bit_2(int number, int index) { return number | (1U << index); }
