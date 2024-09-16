#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "../s21_decimal.h"

static float src[] = {
    0.f,
    1E-28f,
    1.00000003E-27f,
    1.19999996E-27f,
    1.50000004E-27f,
    1.89999999E-27f,
    9.99999989E-27f,
    1.23000001E-26f,
    1.50999995E-26f,
    1.89999999E-26f,
    1.00000002E-25f,
    1.23699997E-25f,
    1.51899999E-25f,
    1.90599999E-25f,
    1.00000002E-24f,
    2.21370009E-24f,
    7.51489961E-24f,
    4.91059997E-24f,
    1E-23f,
    2.21370005E-23f,
    7.51148999E-23f,
    4.94105994E-23f,
    1.10000002E-22f,
    2.21327006E-22f,
    7.51419017E-22f,
    4.91095979E-22f,
    1.09999997E-21f,
    2.21369991E-21f,
    7.51490032E-21f,
    4.91060012E-21f,
    1.09999997E-20f,
    2.21369995E-20f,
    7.51490032E-20f,
    4.91060003E-20f,
    1.10000003E-19f,
    2.21369998E-19f,
    7.51490019E-19f,
    4.9106001E-19f,
    1.09999998E-18f,
    2.21369993E-18f,
    7.5149003E-18f,
    4.91059989E-18f,
    1.1E-17f,
    2.21369993E-17f,
    7.51490013E-17f,
    4.91060006E-17f,
    1.1E-16f,
    2.21369996E-16f,
    7.51490013E-16f,
    4.91059993E-16f,
    1.09999997E-15f,
    2.21370007E-15f,
    7.51490002E-15f,
    4.91059982E-15f,
    1.10000001E-14f,
    2.21369994E-14f,
    7.51490002E-14f,
    4.91059999E-14f,
    1.10000001E-13f,
    2.21370001E-13f,
    7.51490016E-13f,
    4.91059992E-13f,
    1.09999997E-12f,
    2.21369993E-12f,
    7.51490016E-12f,
    4.91060014E-12f,
    1.10000004E-11f,
    2.21370006E-11f,
    7.51489981E-11f,
    4.91060005E-11f,
    1.10000002E-10f,
    2.21370006E-10f,
    7.51489981E-10f,
    4.91060026E-10f,
    1.09999998E-09f,
    2.21369989E-09f,
    7.51489981E-09f,
    4.91059993E-09f,
    1.1E-08f,
    2.21369998E-08f,
    7.51490035E-08f,
    4.91059993E-08f,
    1.10000002E-07f,
    2.21370001E-07f,
    7.51490006E-07f,
    4.91060007E-07f,
    1.09999996E-06f,
    2.2137001E-06f,
    7.51490006E-06f,
    4.91060018E-06f,
    1.10000001E-05f,
    2.21369992E-05f,
    7.51490006E-05f,
    4.91059982E-05f,
    0.000110000001f,
    0.000221370006f,
    0.000751490006f,
    0.000491060026f,
    0.00109999999f,
    0.00221369998f,
    0.00751490006f,
    0.00491059991f,
    0.0109999999f,
    0.0221369993f,
    0.0751489997f,
    0.0491060019f,
    0.109999999f,
    0.221369997f,
    0.751489997f,
    0.491059989f,
    1.00999999f,
    1.00730002f,
    1.100281f,
    1.83182812f,
    2.38182998f,
    -0.f,
    -1.f,
    1.f,
    -2.f,
    2.f,
    -3.f,
    3.f,
    -10.f,
    10.f,
    -128.f,
    127.f,
    255.f,
    -32768.f,
    32767.f,
    -32767.f,
    137.f,
    342.f,
    -32860.f,
    33223.f,
    56210.f,
    -65535.f,
    65535.f,
    212818288.f,
    -2818281.f,
    -2147483650.f,
    100.f,
    1782.f,
    -821821.f,
    218128.f,
    9999.f,
    -9999999.f,
    2147483650.f,
    -2147483650.f,
    0.120010003f,
    0.465000004f,
    0.0465000011f,
    4.65000012E-05f,
    0.999999881f,
    16253.0186f,
    1E-28f,
    -9999999440000000000000000000.f,
    12345678.f,
    1234567.5f,
    1234567.88f,
    -0.00167000003f,
    19.9999981f,
    -0.923458755f,
    70172132300000000000000000000.f,
    7211721240000000000000000000.f,
    734172150000000000000000000.f,
    74172130500000000000000000.f,
    7517213080000000000000000.f,
    761721331000000000000000.f,
    72172129600000000000000.f,
    7312172140000000000000.f,
    774721734000000000000.f,
    74231170200000000000.f,
    7858172220000000000.f,
    718667188000000000.f,
    71729664700000000.f,
    7172868650000000.f,
    717212092000000.f,
    0.00000000000000000000000000016929383838292f,
    0.00000000000000000000000858598287381972f,
};

static s21_decimal dst[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000001
    {{0x00000001, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000000001
    {{0x0000000C, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000012
    {{0x0000000F, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000015
    {{0x00000013, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000019
    {{0x00000001, 0x00000000, 0x00000000,
      0x001A0000}},  // 0.00000000000000000000000001
    {{0x0000007B, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000123
    {{0x00000097, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000151
    {{0x00000013, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000000019
    {{0x00000001, 0x00000000, 0x00000000,
      0x00190000}},  // 0.0000000000000000000000001
    {{0x000004D5, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000001237
    {{0x000005EF, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000001519
    {{0x00000772, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000001906
    {{0x00000001, 0x00000000, 0x00000000,
      0x00180000}},  // 0.000000000000000000000001
    {{0x00005679, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000049106
    {{0x00000001, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000000001
    {{0x00005679, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000022137
    {{0x000B762D, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000751149
    {{0x00078A1A, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000494106
    {{0x0000000B, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000000011
    {{0x0003608F, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000221327
    {{0x000B773B, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000751419
    {{0x00077E58, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000491096
    {{0x0000000B, 0x00000000, 0x00000000,
      0x00160000}},  // 0.0000000000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00190000}},  // 0.0000000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00190000}},  // 0.0000000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00190000}},  // 0.0000000000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000,
      0x00150000}},  // 0.000000000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00180000}},  // 0.000000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00180000}},  // 0.000000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00180000}},  // 0.000000000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000,
      0x00140000}},  // 0.00000000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000,
      0x00130000}},  // 0.0000000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00160000}},  // 0.0000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00160000}},  // 0.0000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00160000}},  // 0.0000000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00150000}},  // 0.000000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00150000}},  // 0.000000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00150000}},  // 0.000000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00110000}},  // 0.00000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00140000}},  // 0.00000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00140000}},  // 0.00000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00140000}},  // 0.00000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00100000}},  // 0.0000000000000011
    {{0x00005679, 0x00000000, 0x00000000,
      0x00130000}},  // 0.0000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000,
      0x00130000}},  // 0.0000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000,
      0x00130000}},  // 0.0000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000F0000}},  // 0.000000000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x00110000}},  // 0.00000000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00110000}},  // 0.00000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00110000}},  // 0.00000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000D0000}},  // 0.0000000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x00100000}},  // 0.0000000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00100000}},  // 0.0000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00100000}},  // 0.0000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000C0000}},  // 0.000000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000F0000}},  // 0.000000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000F0000}},  // 0.000000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000F0000}},  // 0.000000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000B0000}},  // 0.00000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000D0000}},  // 0.0000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000D0000}},  // 0.0000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000D0000}},  // 0.0000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00090000}},  // 0.000000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000C0000}},  // 0.000000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000C0000}},  // 0.000000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000C0000}},  // 0.000000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00080000}},  // 0.00000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000B0000}},  // 0.00000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000B0000}},  // 0.00000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000B0000}},  // 0.00000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00070000}},  // 0.0000011
    {{0x00005679, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00060000}},  // 0.000011
    {{0x00005679, 0x00000000, 0x00000000, 0x00090000}},  // 0.000022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00090000}},  // 0.000075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00090000}},  // 0.000049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00050000}},  // 0.00011
    {{0x00005679, 0x00000000, 0x00000000, 0x00080000}},  // 0.00022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00080000}},  // 0.00075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00080000}},  // 0.00049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00040000}},  // 0.0011
    {{0x00005679, 0x00000000, 0x00000000, 0x00070000}},  // 0.0022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00070000}},  // 0.0075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00070000}},  // 0.0049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00030000}},  // 0.011
    {{0x00005679, 0x00000000, 0x00000000, 0x00060000}},  // 0.022137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00060000}},  // 0.075149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00060000}},  // 0.049106
    {{0x0000000B, 0x00000000, 0x00000000, 0x00020000}},  // 0.11
    {{0x00005679, 0x00000000, 0x00000000, 0x00050000}},  // 0.22137
    {{0x0001258D, 0x00000000, 0x00000000, 0x00050000}},  // 0.75149
    {{0x0000BFD2, 0x00000000, 0x00000000, 0x00050000}},  // 0.49106
    {{0x00000065, 0x00000000, 0x00000000, 0x00020000}},  // 1.01
    {{0x00002759, 0x00000000, 0x00000000, 0x00040000}},  // 1.0073
    {{0x0010C9F9, 0x00000000, 0x00000000, 0x00060000}},  // 1.100281
    {{0x001BF394, 0x00000000, 0x00000000, 0x00060000}},  // 1.831828
    {{0x0003A267, 0x00000000, 0x00000000, 0x00050000}},  // 2.38183
    {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},  // -2
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0x00000003, 0x00000000, 0x00000000, 0x80000000}},  // -3
    {{0x00000003, 0x00000000, 0x00000000, 0x00000000}},  // 3
    {{0x0000000A, 0x00000000, 0x00000000, 0x80000000}},  // -10
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 10
    {{0x00000080, 0x00000000, 0x00000000, 0x80000000}},  // -128
    {{0x0000007F, 0x00000000, 0x00000000, 0x00000000}},  // 127
    {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}},  // 255
    {{0x00008000, 0x00000000, 0x00000000, 0x80000000}},  // -32768
    {{0x00007FFF, 0x00000000, 0x00000000, 0x00000000}},  // 32767
    {{0x00007FFF, 0x00000000, 0x00000000, 0x80000000}},  // -32767
    {{0x00000089, 0x00000000, 0x00000000, 0x00000000}},  // 137
    {{0x00000156, 0x00000000, 0x00000000, 0x00000000}},  // 342
    {{0x0000805C, 0x00000000, 0x00000000, 0x80000000}},  // -32860
    {{0x000081C7, 0x00000000, 0x00000000, 0x00000000}},  // 33223
    {{0x0000DB92, 0x00000000, 0x00000000, 0x00000000}},  // 56210
    {{0x0000FFFF, 0x00000000, 0x00000000, 0x80000000}},  // -65535
    {{0x0000FFFF, 0x00000000, 0x00000000, 0x00000000}},  // 65535
    {{0x0CAF597C, 0x00000000, 0x00000000, 0x00000000}},  // 212818300
    {{0x002B00E9, 0x00000000, 0x00000000, 0x80000000}},  // -2818281
    {{0x80000160, 0x00000000, 0x00000000, 0x80000000}},  // -2147484000
    {{0x00000064, 0x00000000, 0x00000000, 0x00000000}},  // 100
    {{0x000006F6, 0x00000000, 0x00000000, 0x00000000}},  // 1782
    {{0x000C8A3D, 0x00000000, 0x00000000, 0x80000000}},  // -821821
    {{0x00035410, 0x00000000, 0x00000000, 0x00000000}},  // 218128
    {{0x0000270F, 0x00000000, 0x00000000, 0x00000000}},  // 9999
    {{0x0098967F, 0x00000000, 0x00000000, 0x80000000}},  // -9999999
    {{0x80000160, 0x00000000, 0x00000000, 0x00000000}},  // 2147484000
    {{0x80000160, 0x00000000, 0x00000000, 0x80000000}},  // -2147484000
    {{0x00002EE1, 0x00000000, 0x00000000, 0x00050000}},  // 0.12001
    {{0x000001D1, 0x00000000, 0x00000000, 0x00030000}},  // 0.465
    {{0x000001D1, 0x00000000, 0x00000000, 0x00040000}},  // 0.0465
    {{0x000001D1, 0x00000000, 0x00000000, 0x00070000}},  // 0.0000465
    {{0x0098967F, 0x00000000, 0x00000000, 0x00070000}},  // 0.9999999
    {{0x0018CCD6, 0x00000000, 0x00000000, 0x00020000}},  // 16253.02
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000001
    {{0x31600000, 0x085B549B, 0x204FCE28,
      0x80000000}},  // -9999999000000000000000000000
    {{0x00BC6150, 0x00000000, 0x00000000, 0x00000000}},  // 12345680
    {{0x0012D688, 0x00000000, 0x00000000, 0x00000000}},  // 1234568
    {{0x0012D688, 0x00000000, 0x00000000, 0x00000000}},  // 1234568
    {{0x000000A7, 0x00000000, 0x00000000, 0x80050000}},  // -0.00167
    {{0x00000014, 0x00000000, 0x00000000, 0x00000000}},  // 20
    {{0x008CE89C, 0x00000000, 0x00000000, 0x80070000}},  // -0.9234588
    {{0xA9400000, 0xB25EFECA, 0xE2BD0685,
      0x00000000}},  // 70172130000000000000000000000
    {{0x0BA00000, 0xC728D3CE, 0x174D6552,
      0x00000000}},  // 7211721000000000000000000000
    {{0x94900000, 0x4A37B072, 0x025F4AFD,
      0x00000000}},  // 734172100000000000000000000
    {{0x1E480000, 0x3964C4DD, 0x003D5A8F,
      0x00000000}},  // 74172130000000000000000000
    {{0x46540000, 0xEEEB8E94, 0x000637D4,
      0x00000000}},  // 7517213000000000000000000
    {{0x52E20000, 0xFE91F196, 0x0000A14C,
      0x00000000}},  // 761721300000000000000000
    {{0xC0FD0000, 0x75817AAA, 0x00000F48,
      0x00000000}},  // 72172130000000000000000
    {{0xCD9E0000, 0x64C57C73, 0x0000018C,
      0x00000000}},  // 7312172000000000000000
    {{0x9EBE4000, 0xFF6C617F, 0x00000029,
      0x00000000}},  // 774721700000000000000
    {{0x47A22000, 0x062A17D2, 0x00000004, 0x00000000}},  // 74231170000000000000
    {{0xB3EBC000, 0x6D0DD5CC, 0x00000000, 0x00000000}},  // 7858172000000000000
    {{0xBFB98000, 0x09F93802, 0x00000000, 0x00000000}},  // 718667200000000000
    {{0xE828D800, 0x00FED5BE, 0x00000000, 0x00000000}},  // 71729660000000000
    {{0xB4C3F200, 0x00197BAF, 0x00000000, 0x00000000}},  // 7172869000000000
    {{0xF472F900, 0x00028C4C, 0x00000000, 0x00000000}},  // 717212100000000
    {{0x00000002, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000002
    {{0x0000218A, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000000008586
};

static float src_err[] = {0.f,  // nan(""),
                          0.f,  //-nan(""),
                          -INFINITY, INFINITY,    -FLT_MIN, FLT_MIN,  -FLT_MAX,
                          FLT_MAX,
                          0.f,  // powf(2.0, 96),
                          0.f,  //-powf(2.0, 96),
                          0.f,  // powf(1.99, 110),
                          0.f,  //-powf(1.99, 110),
                          1.0e-29,   -1.763e-29f, 8.e28f,   7.99e28f, 9.e28f};

START_TEST(float_to_dec_0) {
  int i = 0;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_1) {
  int i = 1;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_2) {
  int i = 2;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_3) {
  int i = 3;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_4) {
  int i = 4;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_5) {
  int i = 5;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_6) {
  int i = 6;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_7) {
  int i = 7;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_8) {
  int i = 8;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_9) {
  int i = 9;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_10) {
  int i = 10;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_11) {
  int i = 11;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_12) {
  int i = 12;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_13) {
  int i = 13;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_14) {
  int i = 14;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_15) {
  int i = 15;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_16) {
  int i = 16;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_17) {
  int i = 17;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_18) {
  int i = 18;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_19) {
  int i = 19;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_20) {
  int i = 20;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_21) {
  int i = 21;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_22) {
  int i = 22;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_23) {
  int i = 23;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_24) {
  int i = 24;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_25) {
  int i = 25;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_26) {
  int i = 26;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_27) {
  int i = 27;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_28) {
  int i = 28;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_29) {
  int i = 29;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_30) {
  int i = 30;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_31) {
  int i = 31;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_32) {
  int i = 32;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_33) {
  int i = 33;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_34) {
  int i = 34;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_35) {
  int i = 35;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_36) {
  int i = 36;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_37) {
  int i = 37;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_38) {
  int i = 38;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_39) {
  int i = 39;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_40) {
  int i = 40;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_41) {
  int i = 41;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_42) {
  int i = 42;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_43) {
  int i = 43;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_44) {
  int i = 44;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_45) {
  int i = 45;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_46) {
  int i = 46;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_47) {
  int i = 47;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_48) {
  int i = 48;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_49) {
  int i = 49;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_50) {
  int i = 50;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_51) {
  int i = 51;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_52) {
  int i = 52;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_53) {
  int i = 53;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_54) {
  int i = 54;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_55) {
  int i = 55;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_56) {
  int i = 56;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_57) {
  int i = 57;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_58) {
  int i = 58;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_59) {
  int i = 59;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_60) {
  int i = 60;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_61) {
  int i = 61;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_62) {
  int i = 62;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_63) {
  int i = 63;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_64) {
  int i = 64;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_65) {
  int i = 65;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_66) {
  int i = 66;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_67) {
  int i = 67;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_68) {
  int i = 68;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(float_to_dec_69) {
  int i = 69;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src[i], &tmp);
  ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
  ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
  ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
  ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(float_to_dec_error_0) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 0;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_1) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 1;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_2) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 2;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_3) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 3;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_4) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 4;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_5) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 5;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_6) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 6;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_7) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 7;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_8) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 8;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_9) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 9;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_10) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 10;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_11) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 11;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_12) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 12;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_13) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 13;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST
START_TEST(float_to_dec_error_14) {
  src_err[0] = nan("");
  src_err[1] = -nan("");
  src_err[8] = powf(2.0, 96);
  src_err[9] = -powf(2.0, 96);
  src_err[10] = powf(1.99, 110);
  src_err[11] = -powf(1.99, 110);

  int i = 14;
  s21_decimal tmp;
  int ret = s21_from_float_to_decimal(src_err[i], &tmp);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *suite_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_float_to_decimal");
  tc = tcase_create("s21_from_float_to_decimal");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, float_to_dec_0);
    tcase_add_test(tc, float_to_dec_1);
    tcase_add_test(tc, float_to_dec_2);
    tcase_add_test(tc, float_to_dec_3);
    tcase_add_test(tc, float_to_dec_4);
    tcase_add_test(tc, float_to_dec_5);
    tcase_add_test(tc, float_to_dec_6);
    tcase_add_test(tc, float_to_dec_7);
    tcase_add_test(tc, float_to_dec_8);
    tcase_add_test(tc, float_to_dec_9);
    tcase_add_test(tc, float_to_dec_10);
    tcase_add_test(tc, float_to_dec_11);
    tcase_add_test(tc, float_to_dec_12);
    tcase_add_test(tc, float_to_dec_13);
    tcase_add_test(tc, float_to_dec_14);
    tcase_add_test(tc, float_to_dec_15);
    tcase_add_test(tc, float_to_dec_16);
    tcase_add_test(tc, float_to_dec_17);
    tcase_add_test(tc, float_to_dec_18);
    tcase_add_test(tc, float_to_dec_19);
    tcase_add_test(tc, float_to_dec_20);
    tcase_add_test(tc, float_to_dec_21);
    tcase_add_test(tc, float_to_dec_22);
    tcase_add_test(tc, float_to_dec_23);
    tcase_add_test(tc, float_to_dec_24);
    tcase_add_test(tc, float_to_dec_25);
    tcase_add_test(tc, float_to_dec_26);
    tcase_add_test(tc, float_to_dec_27);
    tcase_add_test(tc, float_to_dec_28);
    tcase_add_test(tc, float_to_dec_29);
    tcase_add_test(tc, float_to_dec_30);
    tcase_add_test(tc, float_to_dec_31);
    tcase_add_test(tc, float_to_dec_32);
    tcase_add_test(tc, float_to_dec_33);
    tcase_add_test(tc, float_to_dec_34);
    tcase_add_test(tc, float_to_dec_35);
    tcase_add_test(tc, float_to_dec_36);
    tcase_add_test(tc, float_to_dec_37);
    tcase_add_test(tc, float_to_dec_38);
    tcase_add_test(tc, float_to_dec_39);
    tcase_add_test(tc, float_to_dec_40);
    tcase_add_test(tc, float_to_dec_41);
    tcase_add_test(tc, float_to_dec_42);
    tcase_add_test(tc, float_to_dec_43);
    tcase_add_test(tc, float_to_dec_44);
    tcase_add_test(tc, float_to_dec_45);
    tcase_add_test(tc, float_to_dec_46);
    tcase_add_test(tc, float_to_dec_47);
    tcase_add_test(tc, float_to_dec_48);
    tcase_add_test(tc, float_to_dec_49);
    tcase_add_test(tc, float_to_dec_40);
    tcase_add_test(tc, float_to_dec_41);
    tcase_add_test(tc, float_to_dec_42);
    tcase_add_test(tc, float_to_dec_43);
    tcase_add_test(tc, float_to_dec_44);
    tcase_add_test(tc, float_to_dec_45);
    tcase_add_test(tc, float_to_dec_46);
    tcase_add_test(tc, float_to_dec_47);
    tcase_add_test(tc, float_to_dec_48);
    tcase_add_test(tc, float_to_dec_49);
    tcase_add_test(tc, float_to_dec_50);
    tcase_add_test(tc, float_to_dec_51);
    tcase_add_test(tc, float_to_dec_52);
    tcase_add_test(tc, float_to_dec_53);
    tcase_add_test(tc, float_to_dec_54);
    tcase_add_test(tc, float_to_dec_55);
    tcase_add_test(tc, float_to_dec_56);
    tcase_add_test(tc, float_to_dec_57);
    tcase_add_test(tc, float_to_dec_58);
    tcase_add_test(tc, float_to_dec_59);
    tcase_add_test(tc, float_to_dec_60);
    tcase_add_test(tc, float_to_dec_61);
    tcase_add_test(tc, float_to_dec_62);
    tcase_add_test(tc, float_to_dec_63);
    tcase_add_test(tc, float_to_dec_64);
    tcase_add_test(tc, float_to_dec_65);
    tcase_add_test(tc, float_to_dec_66);
    tcase_add_test(tc, float_to_dec_67);
    tcase_add_test(tc, float_to_dec_68);
    tcase_add_test(tc, float_to_dec_69);
    tcase_add_test(tc, float_to_dec_error_0);
    tcase_add_test(tc, float_to_dec_error_1);
    tcase_add_test(tc, float_to_dec_error_2);
    tcase_add_test(tc, float_to_dec_error_3);
    tcase_add_test(tc, float_to_dec_error_4);
    tcase_add_test(tc, float_to_dec_error_5);
    tcase_add_test(tc, float_to_dec_error_6);
    tcase_add_test(tc, float_to_dec_error_7);
    tcase_add_test(tc, float_to_dec_error_8);
    tcase_add_test(tc, float_to_dec_error_9);
    tcase_add_test(tc, float_to_dec_error_10);
    tcase_add_test(tc, float_to_dec_error_11);
    tcase_add_test(tc, float_to_dec_error_12);
    tcase_add_test(tc, float_to_dec_error_13);
    tcase_add_test(tc, float_to_dec_error_14);
    suite_add_tcase(s, tc);
  }

  return (s);
}
