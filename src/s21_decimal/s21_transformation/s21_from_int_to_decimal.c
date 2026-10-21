#include <limits.h>

#include "../../s21_decimal.h"
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_conversion_result code = S21_CONVERSION_OK;

  if (!dst) {
    code = S21_CONVERSION_ERROR;
  } else {
    *dst = s21_decimal_get_zero();

    if (src < 0) {
      if (src == INT_MIN) {
        // Особый случай для INT_MIN, так как -INT_MIN вызовет переполнение
        dst->bits[0] = (unsigned int)INT_MIN;
      } else {
        dst->bits[0] = (unsigned int)(-src);
      }
      dst->bits[3] = (unsigned int)0x80000000;  // Используем явное приведение к
                                                // unsigned int
    } else {
      dst->bits[0] = (unsigned int)src;
      dst->bits[3] = 0;
    }
  }

  return code;
}
