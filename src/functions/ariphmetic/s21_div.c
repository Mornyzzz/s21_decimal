#include "../../s21_decimal.h"

int s21_div(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_big_decimal big_res = {{0}, 0, 0};
  s21_decimal one = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};   // 1
  s21_decimal temp = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  s21_decimal ten = {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}};   // 10

  memset(big_res.number, '0', BIG_LEN);
  s21_big_to_decimal(big_res, res);

  s21_decimal_to_big(dec1, &big_dec1);
  s21_decimal_to_big(dec2, &big_dec2);
  int pow = big_dec1.power - big_dec2.power;
  int sign = big_dec1.sign != big_dec2.sign;
  big_dec1.sign = 0;
  big_dec1.power = 0;
  big_dec2.sign = 0;
  big_dec2.power = 0;
  s21_big_to_decimal(big_dec1, &dec1);
  s21_big_to_decimal(big_dec2, &dec2);

  //деление на ноль
  if (strchr(big_dec2.number, '1') == NULL) {
    return 3;
  }

  //целая часть
  //делаем делитель в виде большого числа для вычитания
  s21_decimal_copy(&temp, dec2);
  while (s21_mul(temp, ten, &temp) == 0) {
  }
  //вычитаем из делимого делитель и уменьшаем делитель
  while (s21_is_greater_or_equal(dec1, dec2)) {
    s21_mul(*res, ten, res);
    s21_dec_div_10(&temp);
    while (s21_is_greater_or_equal(dec1, temp)) {
      s21_sub(dec1, temp, &dec1);
      s21_add(*res, one, res);
    }
  }
  //добавляем нули в целое число
  while (s21_is_not_equal(dec2, temp)) {
    s21_mul(*res, ten, res);
    s21_dec_div_10(&temp);
  }
  //остаток
  int count = 0;
  while (count != 45) {
    //умножаем остаток на 10
    s21_decimal_to_big(dec1, &big_dec1);
    s21_mul_bin_10(big_dec1.number, big_dec1.number, 1);
    if (strchr(big_dec1.number, '1') == NULL ||
        strchr(big_dec1.number, '1') - big_dec1.number <
            96) {  //слишком большой остаток или он ноль
      break;
    }
    s21_big_to_decimal(big_dec1, &dec1);
    //умножаем результат на 10
    s21_decimal_to_big(*res, &big_res);
    s21_mul_bin_10(big_res.number, big_res.number, 1);
    if (strchr(big_res.number, '1') != NULL &&
        strchr(big_res.number, '1') - big_res.number <
            96) {  //слишком большое число
      //банковское округление
      int frac = 0;
      while (s21_is_greater_or_equal(dec1, dec2)) {
        s21_sub(dec1, dec2, &dec1);
        frac++;
      }
      int even = big_res.number[191] == '0' ? 1 : 0;
      if ((frac >= 6) || (!even && frac == 5)) {
        s21_add(*res, one, res);
      }
      break;
    }
    pow++;
    s21_big_to_decimal(big_res, res);
    //получаем целую часть через вычитание и записываем в res
    while (s21_is_greater_or_equal(dec1, dec2)) {
      s21_sub(dec1, dec2, &dec1);
      s21_add(*res, one, res);
    }
    count++;
    s21_decimal_to_big(*res, &big_res);
  }

  s21_decimal_to_big(*res, &big_res);
  big_res.power = pow;
  big_res.sign = sign;
  s21_rounding(&big_res);

  //убираем конечные нули
  while (s21_rem_zero(big_res) && big_res.power > 0) {
    char tempq[193] = "";
    s21_div_bin_10(big_res.number, tempq);
    strcpy(big_res.number, tempq);
    if (big_res.power != 0) big_res.power--;
  }
  while (big_res.power < 0) {
    s21_mul_bin_10(big_res.number, big_res.number, 1);
    //если число слишком большое/маленькое
    if (strchr(big_res.number, '1') != NULL &&
        strchr(big_res.number, '1') - big_res.number < 96) {
      return sign + 1;
    }
    big_res.power++;
  }
  //если число слишком большое
  if (big_res.power < 0 && big_res.sign == 0) return 1;
  //если число слишком маленькое
  if (big_res.power < 0 && big_res.sign == 1) return 2;
  s21_big_to_decimal(big_res, res);
  return 0;
}