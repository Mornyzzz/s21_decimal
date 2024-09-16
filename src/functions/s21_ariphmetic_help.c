#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"
#define BIG_LEN 192
#define BIT_LEN 32

//бинарную строку в инт
unsigned int s21_binary_to_int(char* bits) { return strtoul(bits, NULL, 2); }

//инт в бинарную строку
char* s21_int_to_binary(unsigned int num) {
  //переводит unsigned integer число в двоичный массив (3244234255 ->
  //"1101001110101" (единички и нолики в этом примере натыканы на рандом))
  int i = 0;
  char* temp = calloc(33, sizeof(char));
  char* binary = calloc(33, sizeof(char));

  // Преобразуем число в двоичное представление
  while (num > 0) {
    temp[i] = (num % 2) + '0';
    num /= 2;
    i++;
  }
  for (int j = i; j < 32; j++) {
    temp[j] = '0';
  }

  // Реверсируем строку, чтобы получить правильный порядок битов
  for (int j = 0; j < 32; j++) {
    binary[j] = temp[31 - j];
  }
  binary[32] = '\0';
  free(temp);
  return binary;
}

//разворот строки
void s21_str_reverse(char* str) {
  int len = (int)strlen(str);
  char temp[len];
  strcpy(temp, str);
  for (int i = 0; i < len; i++) {
    str[i] = temp[len - i - 1];
  }
  str[len + 1] = '\0';
}

//удаление нулей из начала
char* s21_delete_zero(char* temp) {
  if (strchr(temp, '1') != NULL) {
    return strchr(temp, '1');
  }
  return "";
}

//из биг в обычный децимал
void s21_big_to_decimal(s21_big_decimal x, s21_decimal* dec) {
  //перевод из двоичного массива в биты
  char temp[33] = "";
  for (int i = 0; i < 3; i++) {
    strncpy(temp, x.number + BIG_LEN / 2 + BIT_LEN * i, BIT_LEN);
    dec->bits[2 - i] = s21_binary_to_int(temp);
  }

  //коэф масштабирования и знак
  for (int i = 0; i < BIT_LEN; i++) {
    temp[i] = '0';
  }
  char* power = s21_int_to_binary(x.power);

  for (int i = 16; i <= 23; i++) {
    temp[i - 8] = power[i + 8];
  }
  free(power);
  temp[32] = '\0';
  temp[0] = x.sign + '0';
  dec->bits[3] = s21_binary_to_int(temp);
}

//из обычного в биг децимал
void s21_decimal_to_big(s21_decimal dec, s21_big_decimal* x) {
  //перевод из битов в двоичный массив
  memset(x->number, '0', BIG_LEN);
  char* mask[4];
  char sign_coef[8 + 1];
  for (int i = 0; i < 3; i++) {
    mask[i] = s21_int_to_binary(dec.bits[i]);
    for (int j = 0; j < BIT_LEN; j++) {
      x->number[BIG_LEN / 2 + BIT_LEN * (2 - i) + j] = mask[i][j];
    }
    free(mask[i]);
  }
  x->number[BIG_LEN] = '\0';

  //коэф масштабирования и знак
  mask[3] = s21_int_to_binary(dec.bits[3]);
  for (int i = 16; i <= 23; i++) {
    sign_coef[i - 16] = mask[3][i - 8];  // 8 - 14
  }
  sign_coef[8] = '\0';
  unsigned temp_int = 0;
  for (int i = 0; i < 8; i++) {
    if (sign_coef[7 - i] == '1') {
      temp_int += pow(2, i);
    }
  }
  x->power = temp_int;
  if (mask[3][0] == '1') {
    x->sign = 1;
  }
  free(mask[3]);
}

//вывод биг децимала
void s21_big_print(s21_big_decimal x) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 32; j++) {
      printf("%c", x.number[i * 32 + j]);
    }
    printf(" ");
    if (i == 2) printf("\n");
  }
  printf("  pow: %d  sign: %d \n\n", x.power, x.sign);
}

//сдвиг
void s21_shift(char* number, int count, char* temp) {
  for (int j = 0; j < count; j++) {
    for (int i = 0; i < BIG_LEN - 1; i++) {
      temp[i] = number[i + 1];
    }
    temp[BIG_LEN - 1] = '0';
    temp[BIG_LEN] = '\0';
  }
}

//побитовое сложение двух строк
void s21_common_add(char* first, char* second, char* result) {
  int add = 0;
  for (int i = BIG_LEN - 1; i >= 0; i--) {
    if ((first[i] + second[i] + add == 98) & (i == 0)) {
      result[i] = '1';
    } else if (first[i] + second[i] + add < 98) {
      result[i] = first[i] + second[i] + add - 48;
      add = 0;
    } else if (first[i] + second[i] + add >= 98) {
      result[i] = first[i] + second[i] + add - 50;
      add = 1;
    }
  }
  result[BIG_LEN] = '\0';
}

//побитовое вычитание двух строк (через сложение)
void s21_common_sub(char* first, char* second, char* result) {
  s21_inverse(second);  // инвертируем число
  char temp[193] =
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000001";
  s21_common_add(second, temp,
                 second);  // добавляем '1' к инвертированному числу
  s21_common_add(first, second, result);

  //переполнение
  if (result[0] + 48 == '0') {
    result[0] = '1';
  }

  //обнуляем старший бит
  char* ptr = strchr(result, '1');
  int index;
  if (ptr != NULL) {
    index = ptr - result;
    result[index] = '0';
  }
}

//деление на 10 столбиком
void s21_div_bin_10(char* number, char* result) {
  char temp[6] = "";
  char ch[2];
  int index_num = 0;
  char num[193] = "";

  if (strchr(number, '1') == NULL) {
    strcpy(num, number);
    memset(result, '0', BIG_LEN - strlen(result));
    for (int i = 0; i < (int)strlen(num); i++) {
      result[i + BIG_LEN - strlen(num)] = num[i];
    }
    return;
  }
  strcpy(num, s21_delete_zero(number));
  int len_num = (int)strlen(num);

  //пока можем брать разряды из числа
  while (index_num != len_num) {
    //пока выносим разряды для вычитания 1010
    while (s21_binary_to_int(temp) < s21_binary_to_int("1010")) {
      sprintf(ch, "%c", num[index_num]);
      strcat(temp, ch);  //записываем разряд

      if (s21_binary_to_int(temp) ==
          0) {  //если в переменной что-то типа "0000"
        char* d = "0";
        strcpy(temp, d);
      }
      index_num++;
      //если можем вычесть 1010 - выходим
      if (s21_binary_to_int(temp) >= s21_binary_to_int("1010")) {
        break;
      }
      //добавляем в результат 0 - число меньше 1010
      char* d = "0";
      strcat(result, d);

      //если вынесли все разряды
      if (index_num == len_num) {
        strcpy(num, result);
        //заполняем нулями (для представления числа в 192 битах)
        memset(result, '0', BIG_LEN - strlen(result));
        //заполняем число
        for (int i = 0; i < (int)strlen(num); i++) {
          result[i + BIG_LEN - strlen(num)] = num[i];
        }
        return;
      }
    }
    //вычли 1010
    char* d = "1";
    strcat(result, d);
    char* qwe =
        s21_int_to_binary(s21_binary_to_int(temp) - s21_binary_to_int("1010"));
    //записываем в переменную остаток
    strcpy(temp, s21_delete_zero(qwe));
    free(qwe);
  }
  strcpy(num, result);
  memset(result, '0', BIG_LEN - strlen(result));
  for (int i = 0; i < (int)strlen(num); i++) {
    result[i + BIG_LEN - strlen(num)] = num[i];
  }
}

//умножение на 10 через сдвиги
void s21_mul_bin_10(char* num, char* result, int count) {
  char temp[BIG_LEN + 1];
  strcpy(temp, num);

  // выполняем умножение на 10
  for (int i = 0; i < count; i++) {
    memset(result, '0', BIG_LEN);  // обнуляем массив
    s21_shift(temp, 1, temp);
    s21_common_add(temp, result, result);
    s21_shift(temp, 2, temp);
    s21_common_add(temp, result, result);
    strcpy(temp, result);
  }

  if (count == 0) {
    strcpy(result, num);
  }
}

//инвертирование бинарной строки
void s21_inverse(char* num) {
  for (int i = 0; i < (int)strlen(num); i++) {
    if (num[i] == '0')
      num[i] = '1';
    else
      num[i] = '0';
  }
}

//округление
void s21_rounding(s21_big_decimal* big_res) {
  char qwe[193] = "";
  char help[193] = "";
  char round_help[193] = "";
  strcpy(round_help, big_res->number);
  while ((strchr(big_res->number, '1') != NULL &&
          strchr(big_res->number, '1') - big_res->number < 96) ||
         (big_res->power > 28)) {
    memset(qwe, '\0', 193);
    s21_div_bin_10(big_res->number, qwe);

    if (big_res->power == 1 ||
        (strchr(qwe, '1') != NULL && strchr(qwe, '1') - qwe > 95)) {
      memset(help, '\0', 193);
      s21_mul_bin_10(qwe, help, 1);
      s21_common_sub(big_res->number, help, help);
      int even = qwe[191] == '0'
                     ? 1
                     : 0;  // 1 - у деленного на 10 числа (значение до запятой)
      int frac =
          s21_binary_to_int(help);  // 6 - число, от которого зависит округление
      if ((frac >= 6) || (!even && frac == 5)) {
        char temp[193] =
            "000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000001";
        s21_common_add(qwe, temp, qwe);
      } else if (even && frac == 5) {
        s21_common_sub(round_help, big_res->number, round_help);
        if (strchr(round_help, '1') != NULL) {
          char temp[193] =
              "0000000000000000000000000000000000000000000000000000000000000000"
              "0000000000000000000000000000000000000000000000000000000000000000"
              "000000000000000000000000000000000000000000000000000000000000000"
              "1";
          s21_common_add(qwe, temp, qwe);
        }
      }
    }
    strcpy(big_res->number, qwe);
    big_res->power--;
  }
}

void s21_decimal_copy(s21_decimal* dest, s21_decimal source) {
  for (int i = 0; i < 3; i++) {
    dest->bits[i] = source.bits[i];
  }
}

//деление на 10 децимала
void s21_dec_div_10(s21_decimal* dec) {
  s21_big_decimal big_dec = {{0}, 0, 0};
  char temp[193] = "";
  s21_decimal_to_big(*dec, &big_dec);
  s21_div_bin_10(big_dec.number, temp);
  strcpy(big_dec.number, temp);
  s21_big_to_decimal(big_dec, dec);
}

//лишние нули
int s21_rem_zero(s21_big_decimal big_dec) {
  char temp[193] = "";
  s21_div_bin_10(big_dec.number, temp);
  s21_mul_bin_10(temp, temp, 1);
  return !(strcmp(temp, big_dec.number));
}

void s21_normalization(s21_decimal dec1, s21_big_decimal* res) {
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_decimal_to_big(dec1, &big_dec1);
  while (big_dec1.power < 28) {
    s21_mul_bin_10(big_dec1.number, big_dec1.number, 1);
    big_dec1.power++;
  }
  strcpy(res->number, big_dec1.number);
  res->sign = big_dec1.sign;
  res->power = big_dec1.power;
}

//    char zxc[193] =
//    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100";
//    char zxc1[193] =
//    "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110110";
//    common_sub(zxc, zxc1, res);

//    char res[193] = "";
//    div_bin_10
//    ("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111000000000000001100000000000000011111111111111111111",
//    res); print(res);
//    //11001100110011001001100110011001100110011001101001100110011001100
//    mul_bin_10("000000000000000000011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011111111111111111111110011001100110101100110011001101100110010101",
//    res, 1); print(res);

// 79228162514264337593543950335
// 792281625142643375935439503356 -> 6