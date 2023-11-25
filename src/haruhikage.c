// #include <lint.h>
// #include <8052.h>

// #define BEEP P0_7

// //_表示升半音
// // 休止符
// #define P 0
// // L表示低音
// #define L1 1
// #define L1_ 2
// #define L2 3
// #define L2_ 4
// #define L3 5
// #define L4 6
// #define L4_ 7
// #define L5 8
// #define L5_ 9
// #define L6 10
// #define L6_ 11
// #define L7 12
// // M表示中音
// #define M1 13
// #define M1_ 14
// #define M2 15
// #define M2_ 16
// #define M3 17
// #define M4 18
// #define M4_ 19
// #define M5 20
// #define M5_ 21
// #define M6 22
// #define M6_ 23
// #define M7 24
// // H表示高音
// #define H1 25
// #define H1_ 26
// #define H2 27
// #define H2_ 28
// #define H3 29
// #define H4 30
// #define H4_ 31
// #define H5 32
// #define H5_ 33
// #define H6 34
// #define H6_ 35
// #define H7 36
// #define STOP 37

unsigned int FreqTable[] = {
    0, 63777, 63872, 63969, 64054, 64140, 64216, 64291, 64360, 64426,
    64489, 64547, 64603, 64655, 64704, 64751, 64795, 64837, 64876, 64913,
    64948, 64981, 65012, 65042, 65070, 65095, 65120, 65144, 65166, 65186,
    65206, 65225, 65242, 65259, 65274, 65289, 65303};

// // 1为半拍

// // void Timer0_Init();

// unsigned char FreqSelect, MusicSelect;

// // void main()
// // {
// //     Timer0_Init();
// // }

// // void Timer0_Init()
// // {
// //     // 控制寄存器
// //     // 或遇到0保持原状态，所以16进制某位为0即该四位2进制保持不变
// //     TMOD |= 0x01;

// //     // 机器周期约1us(1.085us)，时钟周期约1/12us，计时器算机器周期

// //     // 设置初值0x4C00，即按1.085us计50ms
// //     TH0 = 0x4C;
// //     TL0 = 0x00;

// //     TR0 = 1;
// // }

// // void Time0_ISR() __interrupt(1)
// // {
// //     for (int i = 1 * 140; i < 37 * 140; i++)
// //     {
// //         TH0 = FreqTable[i / 140] / 256;
// //         TL0 = FreqTable[i / 140] % 256;
// //         BEEP = !BEEP;
// //     }
// // }

// // void Time0_ISR() __interrupt(1)
// // {
// //         if (FreqTable[FreqSelect])
// //         {
// //             TH0 = FreqTable[FreqSelect] / 256;
// //             TL0 = FreqTable[FreqSelect] % 256;
// //             BEEP = !BEEP;
// //         }
// // }

// void Timer0_Init()
// {
//     TMOD &= 0xF0;
//     TMOD |= 0x01;
//     TH0 = 0xDC;
//     TL0 = 0x00; // 初始10ms溢出
//     TF0 = 0;
//     TR0 = 1;
//     ET0 = 1; // 允许中断
//     EA = 1;  // 允许总中断
//     PT0 = 0; // 低优先级
// }

// void Timer0_Routine() __interrupt(1)
// {
//     if (FreqTable[FreqSelect])
//     {
//         TH0 = FreqTable[FreqSelect] / 256;
//         TL0 = FreqTable[FreqSelect] % 256;
//         BEEP = !BEEP;
//     }
// }

// void Delayms(unsigned int xms) //@11.0592MHz
// {
//     unsigned char __data i, j;
//     while (xms--)
//     {
//         i = 2;
//         j = 199;
//         do
//         {
//             while (--j)
//                 ;
//         } while (--i);
//     }
// }

// void main()
// {
//     Timer0_Init();
//     while (1)
//     {
//         if (FreqSelect == STOP)
//         { // 判断停止
//             TR0 = 0;
//             while (1)
//                 ;
//         }
//         else
//         {
//             FreqSelect = Music[MusicSelect][0];
//             // Delayms(140 * Music[MusicSelect][1]); // 194BPM (60/194)/2=0.155s 155有点慢不懂为啥。。140差不多但还得调整
//             Delayms(90 * Music[MusicSelect][1]); // 194BPM (60/194)/2=0.155s 155有点慢不懂为啥。。140差不多但还得调整
//             MusicSelect++;

//             TR0 = 0; // 音符之间间断
//             Delayms(5);
//             TR0 = 1;
//         }
//     }
// }
