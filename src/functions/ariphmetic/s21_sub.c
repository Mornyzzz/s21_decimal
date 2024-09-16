#include "../../s21_decimal.h"

int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  s21_big_decimal temp = {{0}, 0, 0};
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_big_decimal big_res = {{0}, 0, 0};
  memset(big_res.number, '0', BIG_LEN);
  int sign;
  int op = 0;
  //меняем знак второго числа на противоположный (приводим к сложению двух
  //чисел)
  s21_decimal_to_big(dec2, &temp);
  temp.sign = !temp.sign;
  s21_big_to_decimal(temp, &dec2);
  //большее по модулю число в big_dec1
  if (s21_is_greater_value(dec1, dec2)) {
    s21_decimal_to_big(dec1, &big_dec1);
    s21_decimal_to_big(dec2, &big_dec2);
    sign = big_dec1.sign;
  } else {
    s21_decimal_to_big(dec2, &big_dec1);
    s21_decimal_to_big(dec1, &big_dec2);
    sign = big_dec2.sign;
  }
  //находим разницу степеней 10
  int diff = abs(big_dec1.power - big_dec2.power);
  //нормализуем числа
  if (big_dec1.power > big_dec2.power) {
    s21_mul_bin_10(big_dec2.number, big_res.number, diff);
    big_dec2.power += diff;
    strcpy(big_dec2.number, big_res.number);
  } else if (big_dec1.power < big_dec2.power) {
    s21_mul_bin_10(big_dec1.number, big_res.number, diff);
    big_dec1.power += diff;
    strcpy(big_dec1.number, big_res.number);
  }
  /* если знаки равны - это сложение: первое число + второе число */
  /* если знаки не равны - это вычитание, которое представляет собой следующее:
                              первое число + (инвертированное второе число + 1);
     отброс старшего разряда */
  if (big_dec2.sign != big_dec1.sign) {
    s21_inverse(big_dec2.number);  // инвертируем число
    char temp[193] =
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000001";
    s21_common_add(big_dec2.number, temp,
                   big_dec2.number);  // добавляем '1' к инвертированному числу
    op = 1;
  }
  big_dec2.sign = big_dec1.sign;  // знак большего сохраняется
  //сложение
  s21_common_add(big_dec1.number, big_dec2.number, big_res.number);
  big_res.power = big_dec1.power;
  big_res.sign = big_dec1.sign;
  //отброс старшего разряда
  if (op == 1) {
    char *ptr = strchr(big_res.number, '1');
    int index;
    if (ptr != NULL) {
      index = ptr - big_res.number;
      big_res.number[index] = '0';
    }
  }
  //округление
  s21_rounding(&big_res);
  //-0 и +0
  if (strchr(big_res.number, '1') == NULL) {
    big_res.sign = sign;
  }
  //если число слишком большое
  if (big_res.power < 0 && big_res.sign == 0) return 1;
  //если число слишком маленькое
  if (big_res.power < 0 && big_res.sign == 1) return 2;
  s21_big_to_decimal(big_res, res);
  return 0;
}
