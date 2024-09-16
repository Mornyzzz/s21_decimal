#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    return error = 1;
  }
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int exp = s21_stepen(value);
  if (exp == -1) {
    return error = 1;
  }

  if (exp != 0) {
    s21_decimal buf = {0};
    buf = value;
    s21_truncate_buff(&buf, exp);
    *result = buf;
  } else {
    *result = value;
  }

  return error;
}