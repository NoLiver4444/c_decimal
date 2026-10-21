#ifndef SRC_S21_DECIMAL_S21_TYPES_H
#define SRC_S21_DECIMAL_S21_TYPES_H

#include <stdint.h>
#include <stdio.h>

// Общее количество бит в decimal
#define MAX_BITS 128

// Общее количество бит в одном элементе массива
#define MAX_BLOCK_BITS 32

// Общее количество бит основания decimal (целого числа, которое хранит значение
// decimal)
#define MAX_BLOCK_NUMBER 96

// Structure decimal
typedef struct {
  int bits[4];
} s21_decimal;

// Структура для больших int чисел
typedef struct {
  s21_decimal decimal[2];
} s21_int_256;

typedef union decimal_bit3 {
  int i;
  struct {
    uint32_t empty2 : 16;
    uint32_t power : 8;
    uint32_t empty1 : 7;
    uint32_t sign : 1;
  } parts;
} decimal_bit3;

/**
 * 0 - положительный decimal
 * 1 - отрицательный decimal
 */
typedef enum s21_decimal_sign {
  S21_POSITIVE = 0,
  S21_NEGATIVE = 1
} s21_decimal_sign;

typedef enum s21_comparison_result {
  S21_COMPARISON_FALSE = 0,
  S21_COMPARISON_TRUE = 1,
} s21_comparison_result;

typedef enum s21_other_result {
  S21_OTHER_OK = 0,
  S21_OTHER_ERROR = 1
} s21_other_result;

#endif  // SRC_S21_DECIMAL_S21_TYPES_H
