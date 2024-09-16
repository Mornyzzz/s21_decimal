#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int error = 0;
  // const int POSITIVE = 0;
  const int NEGATIVE = 1;

  s21_decimal temp = {0};
  s21_truncate(value, &temp);

  int exp = s21_stepen(value);
  if (exp == -1) {
    error = 1;
  } else if (exp != 0) {
    int sign = s21_get_sign(value);
    s21_truncate(value, result);

    if (sign == NEGATIVE && s21_is_not_equal(value, temp)) {
      s21_decimal one = {0};
      one.bits[0] = 1;
      s21_sub(*result, one, result);
    }
  } else {
    *result = value;
  }

  return error;
}