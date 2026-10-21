#ifndef SRC_S21_DECIMAL_S21_SIMPLE_S21_SIMPLE_H
#define SRC_S21_DECIMAL_S21_SIMPLE_S21_SIMPLE_H

#include "../../s21_types.h"

/* Declarations of functions */
// s21_get_bit
int s21_get_bit_arnoldea(const s21_decimal *value, int bit_index);
void s21_set_bit_arnoldea(s21_decimal *value, int bit_index, int bit_value);

// s21_get_set_power
int s21_get_power_arnoldea(const s21_decimal *value);
void s21_set_power_arnoldea(s21_decimal *value, int power);

// s21_get_set_sign
int s21_get_sign_arnoldea(const s21_decimal *value);
void s21_set_sign_arnoldea(s21_decimal *value, int sign);

// s21_print_decimal
void s21_print_decimal_arnoldea(const s21_decimal *value);

#endif  // SRC_S21_DECIMAL_S21_SIMPLE_S21_SIMPLE_H
