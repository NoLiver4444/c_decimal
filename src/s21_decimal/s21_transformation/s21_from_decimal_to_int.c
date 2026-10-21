#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "../../s21_decimal.h"
#include "../s21_comparison/s21_comparison.h"
#include "../s21_simple/simple_dickcart/s21_simple_dickcart.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_conversion_result code = S21_CONVERSION_OK;

  if (!dst) {
    code = S21_CONVERSION_ERROR;
  } else {
    *dst = 0;

    // Получаем масштаб decimal
    int scale = s21_decimal_get_scale(src);
    s21_decimal temp = src;

    // Убираем знак для работы с положительным числом
    int sign = s21_decimal_get_sign(src);
    s21_decimal_set_sign(&temp, S21_POSITIVE);

    // Отбрасываем дробную часть (делим на 10^scale)
    for (int i = 0; i < scale; i++) {
      s21_decimal_div_by_10(&temp);
    }

    // Проверяем, что число помещается в int
    int32_t max_positive = (int32_t)INT_MAX;
    int32_t max_negative = (int32_t)INT_MAX + 1U;

    if (temp.bits[1] != 0 || temp.bits[2] != 0 ||
        (sign == S21_NEGATIVE && temp.bits[0] > max_negative) ||
        (sign == S21_POSITIVE && temp.bits[0] > max_positive)) {
      code = S21_CONVERSION_ERROR;
    } else {
      // Конвертируем младшие 32 бита в int
      *dst = (int)temp.bits[0];

      // Устанавливаем знак
      if (sign == S21_NEGATIVE) {
        if (temp.bits[0] == max_negative) {
          *dst = INT_MIN;
        } else {
          *dst = -*dst;
        }
      }
    }
  }

  return code;
}

// Вспомогательная функция для деления decimal на 10
void s21_decimal_div_by_10(s21_decimal *value) {
  uint64_t remainder = 0;
  uint64_t temp;

  // Обрабатываем старшие биты сначала
  for (int i = 2; i >= 0; i--) {
    temp = remainder << 32 | value->bits[i];
    value->bits[i] = (int32_t)(temp / 10);
    remainder = temp % 10;
  }
}

// Получение масштаба из decimal
int s21_decimal_get_scale(s21_decimal value) {
  return (value.bits[3] >> 16) & 0xFF;
}
