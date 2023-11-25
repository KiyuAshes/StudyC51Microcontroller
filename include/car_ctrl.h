#ifndef CAR_CTRL
#define CAR_CTRL

#include <car_pin.h>
#include <std_int.h>

#define WHITE 0
#define BLACK 1

#define STOP 0
#define TURN_LEFT 1
#define TURN_RIGHT 2
#define GO_FORWARD 3
#define GO_BACK 4

uint8 status = STOP;

void pause()
{
    L_F = 0;
    L_B = 0;

    R_F = 0;
    R_B = 0;

    // STAT_LED = ~(0x0F & STAT);

    // RUN_LED = 1;
    // FIN_LED = 0;
}

void stop()
{
    status = STOP;

    pause();
}

void turn_left()
{

    status = TURN_LEFT;

    L_F = 0;
    L_B = 1;

    R_F = 1;
    R_B = 0;

    // STAT_LED = ~(0x0F & STAT);

    // RUN_LED = 0;
    // FIN_LED = 1;
}

void turn_right()
{
    status = TURN_RIGHT;

    L_F = 1;
    L_B = 0;

    R_F = 0;
    R_B = 1;

    // STAT_LED = ~(0x0F & STAT);

    // RUN_LED = 0;
    // FIN_LED = 1;
}

void go_forword()
{
    status = GO_FORWARD;

    L_F = 1;
    L_B = 0;

    R_F = 1;
    R_B = 0;

    // STAT_LED = ~(0x0F & STAT);

    // RUN_LED = 0;
    // FIN_LED = 1;
}

void go_back()
{
    status = GO_BACK;

    L_F = 0;
    L_B = 1;

    R_F = 0;
    R_B = 1;

    // STAT_LED = ~(0x0F & STAT);

    // RUN_LED = 0;
    // FIN_LED = 1;
}

#endif