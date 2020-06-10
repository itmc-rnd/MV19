#ifndef __DATABASE_H
#define __DATABASE_H

#include "stdbool.h"

typedef enum {STOP,STANDBY,SIMV, PCV, ACV, PSV} modes;

typedef struct{
			  int id;
     		char * message;
			  
	      char * messageType;
	      bool Audio_Paused_available;
	      bool Alarm_Paused_available;
}AlarmData;

#endif

