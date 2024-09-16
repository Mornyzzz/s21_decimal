#include "../../s21_decimal.h"

int s21_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_big_decimal big_res = {{0}, 0, 0};
  memset(big_res.number, '0', BIG_LEN);
  s21_decimal_to_big(dec1, &big_dec1);
  s21_decimal_to_big(dec2, &big_dec2);
  int sign_1 = big_dec1.sign;
  int sign_2 = big_dec2.sign;
  //если знаки разные - это вычитание
  if (big_dec1.sign != big_dec2.sign) {
    big_dec2.sign = !big_dec2.sign;  //делаем из x + (-y) -> x - (+y)
    s21_big_to_decimal(big_dec2, &dec2);
    int result = s21_sub(dec1, dec2, res);
    if (result == 0) {
      s21_decimal_to_big(*res, &big_res);
      //-0 и +0 ежжи
      if (strchr(big_res.number, '1') == NULL) {
        if (sign_1 == 1 && sign_2 == 0)
          big_res.sign = 0;
        else
          big_res.sign = sign_1;
      }
      s21_big_to_decimal(big_res, res);
    } else {
      s21_decimal_to_big(dec2, &big_dec2);
      big_dec2.sign = !big_dec2.sign;  //обратно меняем знак
      s21_big_to_decimal(big_dec2, &dec2);
    }
    return result;
  }
  //находим разницу степеней 10
  int diff = abs(big_dec1.power - big_dec2.power);
  //записываем в dec1 число с большей степенью
  if (big_dec1.power < big_dec2.power) {
    s21_decimal_to_big(dec1, &big_dec2);
    s21_decimal_to_big(dec2, &big_dec1);
  }
  //нормализуем второе число и записываем в результат
  s21_mul_bin_10(big_dec2.number, big_res.number, diff);
  big_res.power = diff;
  //сложение
  s21_common_add(big_dec1.number, big_res.number, big_res.number);
  big_res.power = big_dec1.power;
  big_res.sign = big_dec1.sign;
  //округление
  s21_rounding(&big_res);
  //-0 и +0
  if (strchr(big_res.number, '1') == NULL) {
    big_res.sign = sign_1;
  }
  //если число слишком большое
  if (big_res.power < 0 && big_res.sign == 0) return 1;
  //если число слишком маленькое
  if (big_res.power < 0 && big_res.sign == 1) return 2;
  s21_big_to_decimal(big_res, res);
  return 0;
}