#include <lint.h>
#include <8051.h>

int led = 0;
int time0_count = 0;

void Timer_Init()
{
	// 控制寄存器
	// 或遇到0保持原状态，所以16进制某位为0即该四位2进制保持不变
	TMOD |= 0x01;

	// 机器周期约1us(1.085us)，时钟周期约1/12us，计时器算机器周期

	// 设置初值0x4C00，即按1.085us计50ms
	TH0 = 0x4C;
	TL0 = 0x00;

	// 暂时不启用定时器
	TR0 = 0;
}

void Inter_Init()
{
	// 中断总使能
	EA = 1;

	// 定时器中断使能
	ET0 = 1;

	// INT0 外部中断使能，下降沿触发
	EX1 = 1;
	IT1 = 1;
}

void Time0_ISR() __interrupt(1)
{
	time0_count++;

	if (time0_count == 10)
	{
		// 切换LED状态
		led = (led + 1) % 8;
		P1 = ~(1 << led);

		// 设置初值0x4C00，即按1.085us计50ms
		TH0 = 0x4C;
		TL0 = 0x00;

		time0_count = 0;
	}
}

void INT1_ISR() __interrupt(2){
	TR0 = !TR0;
}

void main()
{
	Timer_Init();
	Inter_Init();

	TR0 = 1;

	P1 = 0xfe;

	// 主事件循环
	while (1)
	{
	}
}