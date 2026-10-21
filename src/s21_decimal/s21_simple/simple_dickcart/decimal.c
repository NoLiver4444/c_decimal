#include "s21_simple_dickcart.h"

// Функция для заполнения decimal
void s21_clear_decimal(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

int s21_decimal_get_empty1(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty1;
}

int s21_decimal_get_empty2(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty2;
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

// Функция для получения максималльного числа (79228162514264337593543950335) в
// формате decimal
s21_decimal s21_decimal_get_max(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  return result;
}

// Функция которая находит ближайший установленный бит к старшему
int s21_decimal_get_not_zero_bit(s21_decimal decimal) {
  int result = -1;
  for (int i = MAX_BITS - 1; i >= 0; i--) {
    if (s21_decimal_is_set_bit(decimal, i)) {
      result = i;
      break;
    }
  }

  return result;
}

// Функция для создания 1 в формате decimal
s21_decimal s21_decimal_get_one(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  result.bits[0] = 1;

  return result;
}

// Функция для создания 10 в формате decimal
s21_decimal s21_decimal_get_ten(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  result.bits[0] = 10;

  return result;
}

// Функция длоя создания пустого массива
s21_decimal s21_decimal_get_zero(void) {
  s21_decimal result;
  s21_clear_decimal(&result);

  return result;
}

// Функция для создания 0.5 в формате decimal
s21_decimal s21_decimal_get_zerofive(void) {
  s21_decimal result = {{0x5, 0x0, 0x0, 0x10000}};

  return result;
}

// Функция для проверки бита под номером index в числе decimal
int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
  return s21_is_set_bit(decimal.bits[index / MAX_BLOCK_BITS],
                        index % MAX_BLOCK_BITS);
}

// Обнуление 4 32-х битного элемента decimal
void s21_decimal_null_service_bits(s21_decimal *value) { value->bits[3] = 0; }

// Функция устанавливает значение 1 для бита номер index в числе decimal
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
  s21_decimal_bit(&decimal, index);

  return decimal;
}

// Функция для проверки decimal
int s21_is_correct_decimal(s21_decimal decimal) {
  int code = 1;

  if (s21_decimal_get_empty1(decimal) != 0 ||
      s21_decimal_get_empty2(decimal) != 0) {
    code = 0;
  } else {
    int power = s21_decimal_get_power(decimal);
    if (power < 0 || power > 28) {
      code = 0;
    }
  }

  return code;
}

// Функция для проверки точности
int s21_decimal_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }

void s21_decimal_bit(s21_decimal *value, int bit_index) {
  value->bits[bit_index / 32] |= 1U << (bit_index % 32);
}

// Функция для выравнивания степеней
void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2,
                          s21_int_256 *value_1_256, s21_int_256 *value_2_256) {
  int power1 = s21_decimal_get_power(value_1);
  int power2 = s21_decimal_get_power(value_2);
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;

  s21_decimal_null_service_bits(&tmp1);
  s21_decimal_null_service_bits(&tmp2);

  if (power1 > power2) {
    *value_1_256 = s21_create_int_256_from_decimal(tmp1);
    *value_2_256 = s21_int_128_binary_multiplication(
        tmp2, s21_int128_get_ten_pow(power1 - power2));
  } else if (power1 < power2) {
    *value_1_256 = s21_int_128_binary_multiplication(
        tmp1, s21_int128_get_ten_pow(power2 - power1));
    *value_2_256 = s21_create_int_256_from_decimal(tmp2);
  } else {
    *value_1_256 = s21_create_int_256_from_decimal(tmp1);
    *value_2_256 = s21_create_int_256_from_decimal(tmp2);
  }
}

// Функция для получения знака
int s21_decimal_get_sign(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.sign;
}

// Возвращает 0.0000000000000000000000000001
s21_decimal s21_decimal_get_min(void) {
  s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};

  return result;
}
