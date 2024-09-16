#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int error = 0;
  int exp = s21_stepen(value);
  int round = s21_last_dig(value, exp);
  int sign = s21_get_sign(value);
  if (exp == -1) {
    error = 1;
  } else if (exp != 0) {
    s21_truncate(value, result);
    s21_decimal one = {0};
    one.bits[0] = 1;

    if (round >= 5 && sign == 0) {
      s21_add(*result, one, result);
    }

    else if (round >= 5 && sign == 1) {
      s21_sub(*result, one, result);
    }
  } else {
    *result = value;
  }
  return error;
}
