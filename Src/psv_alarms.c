#include "psv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int PSV_IPAP,PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int ALARM_PSV_Fr_Maxi,ALARM_PSV_FiO2_Mini,ALARM_PSV_FiO2_Maxi,ALARM_PSV_Vti_Mini,ALARM_PSV_Vti_Maxi,ALARM_PSV_Vte_Mini;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;

float tmp=0.0;

void PSV_Alarms()
{
	 if(ALARM_PSV_Vti_Mini >= PSV_Target_Vt || ALARM_PSV_Vti_Mini >(ALARM_PSV_Vti_Maxi-50))
		{
			 ALARM_RECEIVED=true;
			 ALARM_CODE=88; 
			return;
		}
	 else if(ALARM_PSV_Vti_Maxi <= PSV_Target_Vt || ALARM_PSV_Vti_Maxi <(ALARM_PSV_Vti_Mini+50))
		{
			ALARM_RECEIVED=true;
			ALARM_CODE=89; 
			return;
		} 
		else if(ALARM_PSV_Vte_Mini > PSV_Target_Vt)
		{
			ALARM_RECEIVED=true;
			ALARM_CODE=90; 
      return;
		}
		else if(ALARM_PSV_Fr_Maxi < (PSV_BUR+5))
		{
			 ALARM_RECEIVED=true;
			 ALARM_CODE=91;
			 return;
		}
		else if(ALARM_PSV_FiO2_Mini > (ALARM_PSV_FiO2_Maxi-(ALARM_PSV_FiO2_Maxi*0.1)))
		{
				ALARM_RECEIVED=true;
			  ALARM_CODE=92;
        return;
		}
		else if(ALARM_PSV_FiO2_Mini > (ALARM_PSV_FiO2_Maxi-(ALARM_PSV_FiO2_Maxi*0.1)))
		{
				ALARM_RECEIVED=true;
			  ALARM_CODE=93;
			  return;
		}
				else
			return;
		
    return;
}
