#include "standby_mode.h"
#include "database.h"

extern int turbo_speed_high,turbo_spped_low,raise_step;
extern int duration_high,duration_low;


void STANDBY_Mode(void)
{
	duration_high=500;
	duration_low=500;
	turbo_speed_high=12;
	turbo_spped_low=12;
}

