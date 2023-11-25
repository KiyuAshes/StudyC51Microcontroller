// 机器周期约1us(1.085us)，时钟周期约1/12us，计时器算机器周期
// 设置初值0x4C00，即按1.085us计50ms

#ifndef TIME
#define TIME

// 时间基定义
#define MS_1_BASE_H 0xFC;
#define MS_1_BASE_L 0x66;

#define MS_10_BASE_H 0xDC;
#define MS_10_BASE_L 0x00;

#define MS_50_BASE_H 0x4C;
#define MS_50_BASE_L 0x00;

// 基于50ms时间的定义
#define b50_1s 50
#define b50_5s 250
#define b50_10s 500
#define b50_100ms 2
#define b50_200ms 4
#define b50_400ms 8
#define b50_500ms 10
#define b50_800ms 16

#endif