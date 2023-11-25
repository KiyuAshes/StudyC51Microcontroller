#include <lint.h>
#include <8052.h>
#include <std_int.h>
#include <car_pin.h>
#include <car_ctrl.h>
#include <time_base_50ms.h>

// 初始状态为停止
int count = 0;
int sequ_p = 0;
int front_back_flag = S;
int direction = T;
// int left_speed = STOP_SPEED;
// int right_speed = STOP_SPEED;

void Inter_Init()
{
	// 中断总使能
	EA = 1;

	// 定时器中断使能
	ET0 = 1;
	ET1 = 1;

	// INT0 外部中断使能，下降沿触发
	EX1 = 1;
	IT1 = 1;
}

void Timer_Init()
{
	// 控制寄存器
	// 或遇到0保持原状态，所以16进制某位为0即该四位2进制保持不变
	TMOD |= 0x01;

	// 机器周期约1us(1.085us)，时钟周期约1/12us，计时器算机器周期
	// 设置初值0x4C00，即按1.085us计50ms
	TH0 = T_BASE_H;
	TL0 = T_BASE_L;
	TH1 = MS_1_T_BASE_H;
	TL1 = MS_1_T_BASE_L;

	// 暂时不启用定时器
	TR0 = 0;
	TR1 = 0;
}

void Time0_ISR() __interrupt(1)
{
	// TH0 = 0x24;
	// TL0 = 0x00;

	// // 控制序列移动
	// if (count)
	// {
	// 	count--;
	// }
	// else
	// {
		// is_front = ctrl_sequ[sequ_p][0];
		// direction = ctrl_sequ[sequ_p][1];
		// sequ_p++;
		// 800ms 适合小范围演示
		// count = ms_800;
		// RUN_LED = 0;

// 		switch (is_front)
// 		{
// 		case S:
// 			// TR0 = 0;
// 			// ET0 = 0;
// 			L_F = 0;
// 			L_F_LED = 1;
// 			L_B = 0;
// 			L_B_LED = 1;
// 			R_F = 0;
// 			R_F_LED = 1;
// 			R_B = 0;
// 			R_B_LED = 1;
// 			RUN_LED = 1;
// 			FIN_RED = 0;
// 			break;

// 		case F:
// 			L_F = 1;
// 			R_F = 1;
// 			L_B = 0;
// 			R_B = 0;
// 			L_F_LED = 0;
// 			R_F_LED = 0;
// 			L_B_LED = 1;
// 			R_B_LED = 1;
// 			break;

// 		case B:
// 			L_B = 1;
// 			R_B = 1;
// 			L_F = 0;
// 			R_F = 0;
// 			L_F_LED = 1;
// 			R_F_LED = 1;
// 			R_B_LED = 0;
// 			L_B_LED = 0;
// 			break;
// 		}
// 	}
}

// 轮子控制
void Time1_ISR() __interrupt(3)
{
	// TH1 = MS_1_T_BASE_H;
	// TL1 = MS_1_T_BASE_L;

	// CTRL ^= 1 << F;
	// CTRL ^= 1 << (B + 1);

	// switch (is_front)
	// {
	// case F:
	// 	switch (direction)
	// 	{
	// 	case R:
	// 		R_F = !R_F;
	// 		break;
	// 	case L:
	// 		L_F = !L_F;
	// 		break;
	// 	}
	// 	break;

	// case B:
	// 	switch (direction)
	// 	{
	// 	case R:
	// 		R_B = !R_B;
	// 		break;
	// 	case L:
	// 		L_B = !L_B;
	// 		break;
	// 	}

	// 	break;
	// }
}

// void INT0_ISR() __interrupt(0){

// }

void INT1_ISR() __interrupt(2)
{
	sequ_p = (sequ_p + 1) % 6;
	count = 0;
	RUN_LED = 0;
	FIN_LED = 1;
}

// unsigned char control_list[][2] = {}

main()
{

	Timer_Init();
	Inter_Init();

	TR0 = 1;

	// 11停 10前进 01后退 00停
	// 有时候电机接在上面可能导致写入失败
	// L_F = 1;
	// L_B = 0;
	// R_F = 1;
	// R_B = 0;

	// 主事件循环
	while (1)
	{
		if (STOP_KEY == 0)
		{
			sequ_p = 6;
			count = 0;
			// RUN_LED = 0;
			// FIN_LED = 1;
		}
	}
}