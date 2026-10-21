#include "../s21_simple/simple_arnoldea/s21_simple_arnoldea.h"
#include "s21_arithmetic.h"

// Функция для вычитания
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;
  // Проверяем значения
  if (!result) {
    // Если указатель на result NULL то фиксируем ошибку
    code = S21_ARITHMETIC_ERROR;
  } else if (!s21_is_correct_decimal(value_1) ||
             !s21_is_correct_decimal(value_2)) {
    // Проверка value_1 и value_2 на корректность
    // Фиксируем ошибку и записываем в code и result ошибку
    code = S21_ARITHMETIC_ERROR;
    *result = s21_decimal_get_inf();
  }

  // Если нет ошибок, продолжаем выполнение
  if (code == S21_ARITHMETIC_OK) {
    // Обнуляем result и создаем res
    *result = s21_decimal_get_zero();
    s21_decimal res = s21_decimal_get_zero();

    // Получаем знаки
    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);

    // Проверка знаков
    if (sign1 == S21_POSITIVE && sign2 == S21_POSITIVE) {
      // a_1 > 0 и a_2 > 0
      if (s21_is_greater_or_equal_dickcart(value_1, value_2)) {
        // a_1 >= a_2
        code = s21_sub_handle(value_1, value_2, &res);
      } else {
        // a_1 < a_2
        code = s21_sub_handle(value_2, value_1, &res);
        s21_negate_dickcart(res, &res);
      }
    } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
      // a_1 > 0 и a_2 < 0
      // a_1 - a_2 = a_1 + abs(a_2)
      code = s21_add(value_1, s21_abs(value_2), &res);
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
      // a_1 < 0 и a_2 > 0
      // a_1 - a_2 = -(abs(a_1) + a_2)
      code = s21_add(s21_abs(value_1), value_2, &res);
      s21_negate_dickcart(res, &res);
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
      // a_1 < 0 и a_2 < 0
      if (s21_is_greater_or_equal_dickcart(value_1, value_2)) {
        // a_1 >= a_2
        // a_1 - a_2 = -(abs(a_1) + abs(a_2))
        code = s21_sub_handle(s21_abs(value_2), s21_abs(value_1), &res);
      } else {
        // a_1 < a_2
        // a_1 - a_2 = -(abs(a_1) - abs(a_2))
        code = s21_sub_handle(s21_abs(value_1), s21_abs(value_2), &res);
        s21_negate_dickcart(res, &res);
      }
    }

    // Если знак - и число после вычисление оказалось больше допустимого
    // значения, то меняем ошибку на минимальное значение
    if (s21_decimal_get_sign(res) == S21_NEGATIVE &&
        code == S21_ARITHMETIC_BIG) {
      code = S21_ARITHMETIC_SMALL;
    }

    // Записываем результат
    *result = res;
  }

  return code;
}

int s21_sub_handle(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  // Создаем переменные для хранения чисел больших decimal
  s21_int_256 value_1_256;
  s21_int_256 value_2_256;

  // Определяем степени и находим наибольшую степень
  int power1 = s21_decimal_get_power(value_1);
  int power2 = s21_decimal_get_power(value_2);

  int max_power = s21_max(power1, power2);

  // Выравниваем степени
  s21_decimal_leveling(value_1, value_2, &value_1_256, &value_2_256);

  // Вычитаем числа
  s21_int_256 res = s21_int_256_binary_subtraction(value_1_256, value_2_256);

  // Расчитываем степень 10 на которую надо будет поделить число,
  // чтобы поместить его в decimal
  int shift = s21_int_256_get_shift_to_decimal(res);

  // Находим степень результата
  int res_power = max_power - shift;

  // Анализируем степень результата
  if (res_power < 0) {
    code = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    // Если все в порядке

    // remainder - остаток от деления в формате 256 бит
    // powerten - десять в степени в формате 256 бит
    s21_int_256 remainder =
        s21_create_int_256_from_decimal(s21_decimal_get_zero());
    s21_int_256 powerten =
        s21_create_int_256_from_decimal(s21_int_128_get_ten_pow(shift));

    // Уменьшаем результат, чтобы поместить в decimal
    res = s21_int_256_binary_division(res, powerten, &remainder);

    // Выполняем банковское округление
    s21_set_power(&remainder.decimal[0], shift);
    res.decimal[0] = s21_round_banking(res.decimal[0], remainder.decimal[0]);

    // Устанавливаем степень
    s21_set_power(&res.decimal[0], res_power);

    *result = res.decimal[0];
  }

  return code;
}
