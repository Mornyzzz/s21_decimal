#include "../s21_decimal.h"

//больше ли число по модулю - делаем оба положительными и сравниваем
int s21_is_greater_value(s21_decimal dec1, s21_decimal dec2) {
  s21_decimal new1;
  s21_decimal new2;
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_decimal_to_big(dec1, &big_dec1);
  s21_decimal_to_big(dec2, &big_dec2);
  big_dec1.sign = 0;
  big_dec2.sign = 0;
  s21_big_to_decimal(big_dec1, &new1);
  s21_big_to_decimal(big_dec2, &new2);
  return s21_is_greater(new1, new2);
}