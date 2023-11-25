#ifndef CAR_PIN
#define CAR_PIN

// B是右轮，A是左轮
// 2A和1B是前进

// 控制引脚定义
#define STAT P2
#define L_F P2_0
#define L_B P2_1
#define R_F P2_2
#define R_B P2_3

// 传感器定义
#define L_SEN P2_4
#define R_SEN P2_5

// 指示灯定义
#define STAT_LED P1
#define L_F_LED P1_0
#define L_B_LED P1_1
#define R_F_LED P1_2
#define R_B_LED P1_3
#define RUN_LED P1_6
#define FIN_LED P1_7

// 按键定义
#define SW_KEY P3_3
#define STOP_KEY P3_4

#endif