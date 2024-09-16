#include "../s21_decimal.h"

int s21_get_bit(unsigned int src, int index) {
  return (src & (1 << index)) >> index;
}

void s21_set_bit_conv(unsigned int* src, int index, int bit) {
  if (bit == 1) {
    *src = *src | (1 << index);
  } else if (bit == 0) {
    *src = *src & ~(1 << index);
  }
}

int s21_get_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[3], 31);
}

void s21_set_sign(s21_decimal* decimal, int sign) {
  if (sign >= 0) {
    s21_set_bit_conv(&decimal->bits[3], 31, 0);
  } else {
    s21_set_bit_conv(&decimal->bits[3], 31, 1);
  }
}

void s21_set_decimal_exp(s21_decimal* decimal, int exp) {
  int index = 16;
  while (index < 30) {
    s21_set_bit_conv(&decimal->bits[3], index, s21_get_bit(exp, index - 16));
    index++;
  }
}

int s21_get_decimal_exp(s21_decimal decimal) {
  return (decimal.bits[3] << 1) >> 17;
}

// Степени числа 10
static const s21_decimal all_ten_pows[39] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
    [29] = {{0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x1}},
    [30] = {{0x40000000, 0x4674EDEA, 0x9F2C9CD0, 0xC}},
    [31] = {{0x80000000, 0xC0914B26, 0x37BE2022, 0x7E}},
    [32] = {{0x0, 0x85ACEF81, 0x2D6D415B, 0x4EE}},
    [33] = {{0x0, 0x38C15B0A, 0xC6448D93, 0x314D}},
    [34] = {{0x0, 0x378D8E64, 0xBEAD87C0, 0x1ED09}},
    [35] = {{0x0, 0x2B878FE8, 0x72C74D82, 0x134261}},
    [36] = {{0x0, 0xB34B9F10, 0x7BC90715, 0xC097CE}},
    [37] = {{0x0, 0xF436A0, 0xD5DA46D9, 0x785EE10}},
    [38] = {{0x0, 0x98A2240, 0x5A86C47A, 0x4B3B4CA8}}};

void s21_decimal_set_exp(s21_decimal* decimal, int exp) {
  decimal->bits[3] = decimal->bits[3] + (exp << 16);
}

s21_decimal s21_int128_get_ten_pow(int pow) { return all_ten_pows[pow]; }

void s21_decimal_set_mantissa(s21_decimal* decimal, int number, int drobniy,
                              int* exp) {
  int mantissa = number * 1e6 + drobniy;
  // printf("mantissa = %d\n", mantissa);
  s21_from_int_to_decimal(mantissa, decimal);
  *exp = *exp - 6;

  if (*exp > 0) {
    s21_mul(*decimal, s21_int128_get_ten_pow(*exp), decimal);
  } else if (*exp < 0) {
    if (*exp < -27) {
      s21_div(*decimal, s21_int128_get_ten_pow(27), decimal);
      *exp += 27;
    }
    s21_div(*decimal, s21_int128_get_ten_pow(-*exp), decimal);
  }
  // printf("dec[0] = %d\n", decimal->bits[0]);
  //  set_decimal_exp(decimal, get_decimal_exp(*decimal) - exp);
}

void s21_set_decimal_to_zero(s21_decimal* decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

unsigned int s21_as_uint(int x) { return *((unsigned int*)&x); }

int s21_as_int(unsigned int x) { return *((int*)&x); }

int s21_drop_last_digit(s21_decimal* src) {
  unsigned long long last = 0, div = 0;
  for (int i = 2; i >= 0; i--) {
    last = s21_as_uint(src->bits[i]) + div * 4294967296;
    div = last % 10;
    src->bits[i] = s21_as_int((unsigned int)(last / 10));
  }
  return (int)div;
}

int s21_check_max_limit(int src) {
  int result = 0;
  if (s21_get_bit(src, 31)) {
    for (int i = 30; i >= 0; i--) {
      if (s21_get_bit(src, i)) result = 1;
    }
  }
  return result;
}