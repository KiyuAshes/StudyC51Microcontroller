#include <lint.h>
#include <8052.h>
#include <car_pin.h>
#include <car_ctrl.h>
#include <time.h>

#define PWM 250
#define PWM_MAX 100

uint8 pwm_count = 0;

void Inter_Init();
void Timer_Init();
void Time1_ISR() __interrupt(3);
void DealyMs(unsigned int ms);

void main()
{
	Inter_Init();
	Timer_Init();

	// status = TURN_RIGHT;
	unsigned char flag;

	// 主事件循环
	while (1)
	{

		if (R_SEN == BLACK || L_SEN == BLACK)
		{
			// pause();
			DealyMs(1);
		}

		if ((L_SEN == BLACK) && (R_SEN == WHITE))
			flag = 0;
		else if ((L_SEN == WHITE) && (R_SEN == BLACK))
			flag = 1;
		else if ((L_SEN == BLACK) && (R_SEN == BLACK))
			flag = 2;
		else
			flag = 3;

		switch (flag)
		{
		case 0:
			pwm_count++;
			turn_right();
			break;
		case 1:
			pwm_count++;
			turn_left();
			break;
		case 2:
			stop();
			break;
		case 3:
			go_forword();
			break;
		}

		if (pwm_count > PWM)
		{
			pwm_count = 0;

			go_back();
			DealyMs(100);

			switch (flag)
			{
			case 0:
				turn_right();
				break;
			case 1:
				turn_left();
				break;
			}
			DealyMs(300);
		}

		DealyMs(1);

		// if (R_SEN == BLACK || L_SEN == BLACK)
		// {
		// 	stop();
		// }

		// DealyMs(100);

		// // 左侧碰线左转
		// if (L_SEN == BLACK && R_SEN == WHITE)
		// 	status = TURN_LEFT;

		// // 右侧碰线右转
		// else if (R_SEN == BLACK && L_SEN == WHITE)
		// 	status = TURN_RIGHT;
		// // 正常直行
		// else if (R_SEN == WHITE && L_SEN == WHITE)
		// 	status = GO_FORWARD;
		// // 两侧碰线停车
		// else
		// {
		// 	status = STOP;
		// 	// break;
		// }
	}

	// 函数测试
	// go_forword();
	// go_back();
	// turn_left();
	// turn_right();

	// 引脚测试
	// L_F = 1;
	// L_F_LED = 0;
	// L_B = 0;
	// L_B_LED = 1;
	// R_F = 1;
	// R_F_LED = 0;
	// R_B = 0;
	// R_B_LED = 1;
}

void Inter_Init()
{
	// 中断总使能
	EA = 1;

	// 定时器中断使能
	// ET0 = 1;
	ET1 = 1;

	// INT0 外部中断使能，下降沿触发
	EX1 = 1;
	IT1 = 1;
}

void Timer_Init()
{
	// 控制寄存器
	// 或遇到0保持原状态，所以16进制某位为0即该四位2进制保持不变
	TMOD = 0x11;

	// 定时器初值
	TH0 = 0x00;
	TL0 = 0x00;
	TH1 = 0x00;
	TL1 = 0x00;

	// 启用定时器
	TR0 = 0;
	TR1 = 1;
}

// void Time0_ISR() __interrupt(1)
// {
// }

void Time1_ISR() __interrupt(3)
{
	TH0 = MS_1_BASE_H;
	TL0 = MS_1_BASE_L;

	pwm_count = (pwm_count + 1) % PWM_MAX;

	if (pwm_count < PWM)
	{
		switch (status)
		{
		case STOP:

			stop();

			break;

		case GO_FORWARD:
			go_forword();

			break;

		case GO_BACK:
			go_back();

			break;

		case TURN_LEFT:
			turn_left();

			break;

		case TURN_RIGHT:
			turn_right();

			break;
		}
	}
	else
	{
		pause();
	}
}

void DealyMs(unsigned int ms)
{
	while (ms--)
	{

		TH0 = MS_1_BASE_H;
		TL0 = MS_1_BASE_L;

		TR0 = 1;

		while (!TF0)
		{
		};

		TR0 = 0;
		TF0 = 0;
	}
}
