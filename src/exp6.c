#include <lint.h>
#include <8052.h>
#include <car_pin.h>

#define PWM_PERIOD 255
#define MODE_TRACE 0
#define MODE_AVOID 1

unsigned char mode = MODE_TRACE;
unsigned char pwmWidthLeft = PWM_PERIOD / 2;
unsigned char pwmWidthRight = PWM_PERIOD / 2;

void pwmControl()
{
    static unsigned char pwmCount = 0;

    pwmCount++;
    if (pwmCount >= PWM_PERIOD)
    {
        pwmCount = 0;
    }

    L_F = pwmCount < pwmWidthLeft ? 1 : 0;
    R_B = pwmCount < pwmWidthRight ? 1 : 0;
}

void DelayMs(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++)
    {
        TMOD &= 0xF0;
        TMOD |= 0x01;
        TL0 = 0x18;
        TH0 = 0xFC;
        TR0 = 1;

        while (!TF0)
            ;

        TR0 = 0;
        TF0 = 0;
    }
}

void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
        }
    }
}

void LeftGo()
{
    L_F = 1;
    L_B = 0;
    pwmWidthLeft = PWM_PERIOD / 2;
}

void LeftStop()
{
    L_F = 0;
    L_B = 0;
}

void L_Back()
{
    L_F = 0;
    L_B = 1;
    pwmWidthLeft = PWM_PERIOD / 2;
}

void RightGo()
{
    R_F = 0;
    R_B = 1;
    pwmWidthRight = PWM_PERIOD / 2;
}

void RightStop()
{
    R_F = 0;
    R_B = 0;
}

void R_Back()
{
    R_F = 1;
    R_B = 0;
    pwmWidthRight = PWM_PERIOD / 2;
}

void CarGo()
{
    LeftGo();
    RightGo();
}

void CarBack()
{
    L_Back();
    R_Back();
}

void CarStop()
{
    RightStop();
    LeftStop();
}

void CarLeft()
{
    L_Back();
    RightGO();
}

void CarRight()
{
    LeftGo();
    R_Back();
}

void CarStraightRight(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms / 50; i++)
    {
        LeftGo();
        RightGo();
        delay(25);
        RightStop();
        delay(25);
    }
    CarStop();
}

void TurnRight90()
{
    CarRight();
    delay(2000);
}

void Trace()
{
    unsigned char flag;
    if ((L_SEN == 1) && (R_SEN == 0))
        flag = 0;
    else if ((L_SEN == 0) && (R_SEN == 1))
        flag = 1;
    else if ((L_SEN == 1) && (R_SEN == 1))
        flag = 2;
    else
        flag = 3;
    switch (flag)
    {
    case 0:
        CarRight();
        break;
    case 1:
        CarLeft();
        break;
    case 2:
        CarStop();
        break;
    case 3:
        CarGo();
        break;
    }
}

void AvoidObstacle()
{
    if (L_SEN && R_SEN)
    {
        CarGo();
    }
    else if (L_SEN && !R_SEN)
    {
        CarStop();
        delay(500);
        CarRight();
        delay(1000);
        CarStop();
        delay(500);
    }
    else if (R_SEN && !L_SEN)
    {
        CarStop();
        delay(500);
        CarLeft();RightGo
        delay(1000);
        CarStop();
        delay(500);
    }
    else
    {
        CarStop();
        delay(500);
        Carback();
        delay(2000);
        CarLeft();
        delay(1000);
        CarStop();
        delay(500);
    }
}

void usart_Init()
{
    SCON = 0X50;
    TMOD = 0X2RightGo;
    PCON = 0X80;
    TH1 = 0XFA;
    TL1 = 0XFA;
    ES = 1;
    EA = 1;
    TR1 = 1;
    ET1 = 0;
}

void main()
{
    usartinit();
    while (1)
        ;
}
