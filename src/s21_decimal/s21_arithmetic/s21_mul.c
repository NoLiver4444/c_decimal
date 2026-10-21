#include "s21_arithmetic.h"

// Функция для вычитания
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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
    // Получаем знаки
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);

    // Обнуляем result и создаем res
    s21_decimal res = s21_decimal_get_zero();
    *result = s21_decimal_get_zero();

    // Проверка знаков
    if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
      // a_1 > 0 и a_2 > 0
      code = s21_mul_make(value_1, value_2, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_POSITIVE) {
      // a_1 < 0 и a_2 > 0
      //-(abs(a_1) * a_2)
      code = s21_mul_make(s21_abs(value_1), value_2, &res);
      s21_negate_dickcart(res, &res);
    } else if (sign_1 == S21_POSITIVE && sign_2 == S21_NEGATIVE) {
      // a_1 > 0 и a_2 < 0
      //-(a_1 * abs(a_2))
      code = s21_mul_make(value_1, s21_abs(value_2), &res);
      s21_negate_dickcart(res, &res);
    } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
      // a_1 < 0 и a_2 < 0
      // abs(a_1) * abs(a_2)
      code = s21_mul_make(s21_abs(value_1), s21_abs(value_2), &res);
    }

    // Если знак - и число после вычисление оказалось больше допустимого
    // значения, то меняем ошибку на минимальное значение
    if (code == S21_ARITHMETIC_BIG) {
      if (s21_decimal_get_sign(res) == S21_NEGATIVE) {
        code = S21_ARITHMETIC_SMALL;
      }
    }

    // Обрабатываем ситуацию, что результат получился слишком маленький (0 < |x|
    // < 1e-28)
    if (code == S21_ARITHMETIC_OK &&
        !s21_is_equal_dickcart(value_1, s21_decimal_get_zero()) &&
        !s21_is_equal_dickcart(value_2, s21_decimal_get_zero()) &&
        s21_is_equal_dickcart(res, s21_decimal_get_zero())) {
      code = S21_ARITHMETIC_SMALL;
    }

    // Записываем результат
    *result = res;
  }

  return code;
}

int s21_mul_make(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  // Определяем степени
  int power1 = s21_get_power(&value_1);
  int power2 = s21_get_power(&value_2);

  // зануляем степени чисел
  s21_decimal_null_service_bits(&value_1);
  s21_decimal_null_service_bits(&value_2);

  // Перемножаем множители
  s21_int_256 res = s21_int_128_binary_multiplication(value_1, value_2);

  // Расчитываем степень 10 на которую надо будет поделить число,
  // чтобы поместить его в decimal
  int shift = s21_int_256_get_shift_to_decimal(res);

  // Находим степень результата
  int res_power = power1 + power2 - shift;

  // Анализируем степень результата
  if (res_power < 0) {
    code = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    // Если все в порядке

    // Уменьшаем res чтобы максимальная степень была 28
    while (shift > 28) {
      res = s21_int_256_binary_division(
          res, s21_create_int_256_from_decimal(s21_decimal_get_ten()), NULL);
      --shift;
    }

    // корректируем результат
    if (res_power > 28) {
      s21_int_256 tmp_res = res;
      int tmp_power = res_power;

      while (tmp_power > 28) {
        tmp_res = s21_int_256_binary_division(
            tmp_res, s21_create_int_256_from_decimal(s21_decimal_get_ten()),
            NULL);
        --tmp_power;
      }

      shift = res_power - tmp_power + shift;
      res_power = tmp_power;
    }

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

    // Устанавливаем степень результата
    s21_set_power(&res.decimal[0], res_power);

    // Анализируем результат
    if (!s21_int_128_binary_equal_zero(res.decimal[1]) ||
        !s21_is_correct_decimal(res.decimal[0])) {
      code = S21_ARITHMETIC_BIG;
      *result = s21_decimal_get_inf();
    } else {
      *result = res.decimal[0];
    }
  }

  return code;
}
