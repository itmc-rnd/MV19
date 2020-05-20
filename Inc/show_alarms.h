#ifndef __SHOW_ALARMS_H
#define __SHOW_ALARMS_H

#include "stdbool.h"

typedef struct{
			  int id;
     		char * message;
			  
	      char * messageType;
	      bool Audio_Paused_available;
	      bool Alarm_Paused_available;
}AlarmData;

 #endif
