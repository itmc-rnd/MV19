#include "psv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int PSV_IPAP,PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int ALARM_PSV_Fr_Maxi,ALARM_PSV_FiO2_Mini,ALARM_PSV_FiO2_Maxi,ALARM_PSV_Vti_Mini,ALARM_PSV_Vti_Maxi,ALARM_PSV_Vte_Mini;

void PSV_Alarms()
{
	 if(ALARM_PSV_Vti_Mini >= PSV_Target_Vt || ALARM_PSV_Vti_Mini >(ALARM_PSV_Vti_Maxi-50))
		{
	 create_response_for_raspberry(111,88);
		}
	 else if(ALARM_PSV_Vti_Maxi <= PSV_Target_Vt || ALARM_PSV_Vti_Maxi <(ALARM_PSV_Vti_Mini+50))
		{
			 create_response_for_raspberry(111,89);
		} 
		else if(ALARM_PSV_Vte_Mini > PSV_Target_Vt)
		{
			 create_response_for_raspberry(111,90);
		}
		else if(ALARM_PSV_Fr_Maxi < (PSV_BUR+5))
		{
			 create_response_for_raspberry(111,91);
		}
		else if(ALARM_PSV_FiO2_Mini > (ALARM_PSV_FiO2_Maxi-(ALARM_PSV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,92);
		}
		else if(ALARM_PSV_FiO2_Mini > (ALARM_PSV_FiO2_Maxi-(ALARM_PSV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,93);
		}
}