#include "simv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;
extern int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;

void SIMV_Alarms()
{
	 if(ALARM_SIMV_Pi_Mini < (SIMV_EPAP+2) || ALARM_SIMV_Pi_Mini > SIMV_IPAP || ALARM_SIMV_Pi_Mini > (ALARM_SIMV_Pi_Maxi-10))
		{
	 create_response_for_raspberry(111,76);
		}
	 else if(ALARM_SIMV_Pi_Maxi < (SIMV_EPAP+15) ||ALARM_SIMV_Pi_Maxi <(SIMV_IPAP+2) || ALARM_SIMV_Pi_Maxi <(ALARM_SIMV_Pi_Mini+10))
		{
			 create_response_for_raspberry(111,77);
		} 
		else if(ALARM_SIMV_Vte_Mini > SIMV_Vt)
		{
			 create_response_for_raspberry(111,78);
		}
		else if(ALARM_SIMV_Fr_Maxi < (SIMV_BUR+5))
		{
			 create_response_for_raspberry(111,79);
		}
		else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,80);
		}
		else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,81);
		}
}