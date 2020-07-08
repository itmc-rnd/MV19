#include "standby_mode.h"
#include "database.h"

extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;


void STANDBY_Mode(void)
{
	duration_Ins=500;
	duration_Exp=500;
	turbo_speed_Ins=1;
	turbo_speed_Exp=1;
}

