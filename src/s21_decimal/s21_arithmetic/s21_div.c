#include "s21_arithmetic.h"

// Функция для деления
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  // Проверяем указатель на результат
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  } else if (!s21_is_correct_decimal(value_1) ||
             !s21_is_correct_decimal(value_2)) {
    code = S21_ARITHMETIC_ERROR;
    *result = s21_decimal_get_inf();
  } else if (s21_is_equal_dickcart(value_2, s21_decimal_get_zero())) {
    code = S21_ARITHMETIC_ZERO_DIV;
    *result = s21_decimal_get_inf();
  }

  // Если нет ошибок, продолжаем выполнение
  if (code == S21_ARITHMETIC_OK) {
    // Получаем знаки
    int sign_1 = s21_decimal_get_sign(value_1);
    int sign_2 = s21_decimal_get_sign(value_2);

    // Обнуляем result и создаем res
    *result = s21_decimal_get_zero();
    s21_int_256 res;
    s21_int_256 value_1_256;
    s21_int_256 value_2_256;

    // Выравниваем степени
    s21_decimal_leveling(value_1, value_2, &value_1_256, &value_2_256);

    // Остаток от деления в формате 256 бит
    s21_int_256 remainder =
        s21_create_int_256_from_decimal(s21_decimal_get_zero());

    // Делим числа и записываем в остаток
    res = s21_int_256_binary_division(value_1_256, value_2_256, &remainder);

    // Проверка результата деления
    if (res.decimal[0].bits[3] != 0 ||
        !s21_int_128_binary_equal_zero(res.decimal[1])) {
      if (sign_1 != sign_2) {
        code = S21_ARITHMETIC_SMALL;
      } else {
        code = S21_ARITHMETIC_BIG;
      }
      *result = s21_decimal_get_inf();
    } else {
      // Если все в порядке, продолжаем деление
      code = s21_div_make(value_2_256, res, remainder, result);

      // Устанавливаем знак результата
      if (sign_1 != sign_2) {
        s21_set_sign(result, S21_NEGATIVE);
      }

      // Проверка на превышение допустимого значения
      if (s21_decimal_get_sign(*result) == S21_NEGATIVE &&
          code == S21_ARITHMETIC_BIG) {
        code = S21_ARITHMETIC_SMALL;
      }

      // Проверка на слишком маленький результат
      if (code == S21_ARITHMETIC_OK &&
          !s21_is_equal_dickcart(value_1, s21_decimal_get_zero()) &&
          s21_is_equal_dickcart(*result, s21_decimal_get_zero())) {
        code = S21_ARITHMETIC_SMALL;
      }
    }
  }

  return code;
}

int s21_div_make(s21_int_256 value_2_256, s21_int_256 res,
                 s21_int_256 remainder, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  // power_1 - значение степени результата
  int power_1 = s21_div_calc_fractional(&res, value_2_256, &remainder);

  s21_int_256 tmp_res = s21_create_int_256_from_decimal(s21_decimal_get_zero());

  // Переводим остаток, полученный в расчете выше, в decimal, чтобы использовать
  // его для округления power_2 - значение степени decimal
  int power_2 = s21_div_calc_fractional(&tmp_res, value_2_256, &remainder);
  // Устанавливаем полученную степень для нашего остатка
  s21_decimal_set_power(&tmp_res.decimal[0], power_2);

  if (s21_is_equal_dickcart(tmp_res.decimal[0], s21_decimal_get_zerofive())) {
    if (!s21_int_128_binary_equal_zero(remainder.decimal[0]) ||
        !s21_int_128_binary_equal_zero(remainder.decimal[1])) {
      // Если остаток от деления в виде decimal получился ровно 0.5, но после
      // вычисления остаток от деления не равен 0, то корректируем остаток, т.к.
      // фактически он больше 0.5: 0.5 + 0.0000000000000000000000000001 =
      // 0.5000000000000000000000000001
      s21_add(tmp_res.decimal[0], s21_decimal_get_min(), &tmp_res.decimal[0]);
    }
  }

  // Выполняем банковское округление
  res.decimal[0] = s21_round_banking(res.decimal[0], tmp_res.decimal[0]);
  s21_decimal_set_power(&res.decimal[0], power_1);

  // Анализируем результат
  if (!s21_int_128_binary_equal_zero(res.decimal[1]) ||
      !s21_is_correct_decimal(res.decimal[0])) {
    code = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  } else {
    *result = res.decimal[0];
  }

  return code;
}

// Умножаем остаток на 10 и опять делим на число
int s21_div_calc_fractional(s21_int_256 *res, s21_int_256 value_2_256,
                            s21_int_256 *remainder) {
  int power = 0;
  s21_int_256 number = *res;

  s21_int_256 tmp;
  s21_int_256 tmp_remainder = *remainder;

  // Выполняем действия пока остаток не равен 0 или степень не 28
  while ((!s21_int_128_binary_equal_zero((*remainder).decimal[0]) ||
          !s21_int_128_binary_equal_zero((*remainder).decimal[1])) &&
         power < 28) {
    // Сохраняем значения
    s21_int_256 number_stored = number;
    s21_int_256 remainder_stored = tmp_remainder;

    // Производим расчеты
    number = s21_int_256_binary_multiplication(number, s21_decimal_get_ten());
    tmp_remainder =
        s21_int_256_binary_multiplication(tmp_remainder, s21_decimal_get_ten());
    tmp =
        s21_int_256_binary_division(tmp_remainder, value_2_256, &tmp_remainder);
    number = s21_int_256_binary_addition(number, tmp);

    // Возвращаем сохраненные значения
    if (!s21_is_correct_decimal(number.decimal[0])) {
      number = number_stored;
      tmp_remainder = remainder_stored;
      break;
    }

    ++power;
  }

  *res = number;
  *remainder = tmp_remainder;

  return power;
}
