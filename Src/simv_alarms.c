#include "simv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;
extern int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;

extern int Current_Pressure_Ins,Current_Pressure_Exp,Current_Flow_Ins,Current_Flow_Exp;
extern int SIMV_Vt_Sens;
float simv_tmp=0.0;

void SIMV_Alarms()
{

		
//	 if(ALARM_SIMV_Pi_Mini < (SIMV_EPAP+2) || ALARM_SIMV_Pi_Mini > SIMV_IPAP || ALARM_SIMV_Pi_Mini > (ALARM_SIMV_Pi_Maxi-10))
//		{
			if(Current_Pressure_Ins<ALARM_SIMV_Pi_Mini)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=76;
			  return;
			}
//		}
//	 else if(ALARM_SIMV_Pi_Maxi < (SIMV_EPAP+15) ||ALARM_SIMV_Pi_Maxi <(SIMV_IPAP+2) || ALARM_SIMV_Pi_Maxi <(ALARM_SIMV_Pi_Mini+10))
//		{
			if(Current_Pressure_Ins>ALARM_SIMV_Pi_Maxi)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=77;
        return;
			}	
//		} 
//		else if(ALARM_SIMV_Vte_Mini > SIMV_Vt)
//		{
			if(SIMV_Vt_Sens<ALARM_SIMV_Vte_Mini)
			{
				ALARM_RECEIVED=true;
			  ALARM_CODE=78;
			  return;
			}	
//		}
//		else if(ALARM_SIMV_Fr_Maxi < (SIMV_BUR+5))
//		{
//			  ALARM_RECEIVED=true;
//			  ALARM_CODE=79;
//			
//		}
	/*	else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
			  ALARM_RECEIVED=true;
			  ALARM_CODE=80;
			//create_response_for_raspberry(111,80);
		}
		else if(ALARM_SIMV_FiO2_Mini > (ALARM_SIMV_FiO2_Maxi-(ALARM_SIMV_FiO2_Maxi*0.1)))
		{
			  ALARM_RECEIVED=true;
			  ALARM_CODE=81;
			 //create_response_for_raspberry(111,81);
		}*/
			
		
    return;
}