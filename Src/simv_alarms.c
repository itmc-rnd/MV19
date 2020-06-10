#include "simv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;
extern int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;
int SIMV_IPAP_Sens=0;
extern int Current_P1;
extern int32_t SIMV_Vt_Sens;
float tmp=0.0;

void SIMV_Alarms()
{
		SIMV_IPAP_Sens= Current_P1;
		
	 if(ALARM_SIMV_Pi_Mini < (SIMV_EPAP+2) || ALARM_SIMV_Pi_Mini > SIMV_IPAP || ALARM_SIMV_Pi_Mini > (ALARM_SIMV_Pi_Maxi-10))
		{
			if(SIMV_IPAP_Sens<ALARM_SIMV_Pi_Mini)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=76;
				//create_response_for_raspberry(111,76);
			}
		}
	 else if(ALARM_SIMV_Pi_Maxi < (SIMV_EPAP+15) ||ALARM_SIMV_Pi_Maxi <(SIMV_IPAP+2) || ALARM_SIMV_Pi_Maxi <(ALARM_SIMV_Pi_Mini+10))
		{
			if(SIMV_IPAP_Sens>ALARM_SIMV_Pi_Maxi)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=77;
			 //create_response_for_raspberry(111,77);
			}	
		} 
		else if(ALARM_SIMV_Vte_Mini > SIMV_Vt)
		{
			if(SIMV_Vt_Sens<ALARM_SIMV_Vte_Mini)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=78;
			 //create_response_for_raspberry(111,78);
			}	
		}
		else if(ALARM_SIMV_Fr_Maxi < (SIMV_BUR+5))
		{
			  ALARM_RECEIVED=true;
			  ALARM_CODE=79;
			//create_response_for_raspberry(111,79);
		}
	/*	else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
			  ALARM_RECEIVED=true;
			  ALARM_CODE=80;
			//create_response_for_raspberry(111,80);
		}
		else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
<<<<<<< HEAD
			  ALARM_RECEIVED=true;
			  ALARM_CODE=81;
			 //create_response_for_raspberry(111,81);
		}*/
=======
			 create_response_for_raspberry(111,81);
		}
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
				else
			return;
		
    return;
}