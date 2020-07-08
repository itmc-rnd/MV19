#include "acv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Vt;
extern int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;
extern bool ALARM_Hi,ALARM_Low;

extern int Current_Pressure_Ins,Current_Pressure_Exp,Current_Flow_Ins,Current_Flow_Exp,t3_counter;
int Sum=0,avg=0;

extern int32_t ACV_Vt_Sens;
extern int t3_counter_old,t3_counter;

float Fr;

void ACV_Alarms()
{
			
//	 if(ALARM_ACV_Pi_Mini < (ACV_EPAP+2) || ALARM_ACV_Pi_Mini > (ALARM_ACV_Pi_Maxi-10))
//		{
			if(Current_Pressure_Ins<ALARM_ACV_Pi_Mini)
				{
					ALARM_RECEIVED=true;
					ALARM_Hi=false,ALARM_Low=true;
					ALARM_CODE=82;
					return;
				}
				 if(Current_Pressure_Ins>ALARM_ACV_Pi_Maxi)
				{
					ALARM_RECEIVED=true;
					ALARM_Hi=false,ALARM_Low=true;
					ALARM_CODE=83;
					return;
				}
//		}
//	 else if(ALARM_ACV_Pi_Maxi < (ACV_EPAP+15) || ALARM_ACV_Pi_Maxi <(ALARM_ACV_Pi_Maxi +10))
//		{
				if(ACV_Vt_Sens<ALARM_ACV_Vte_Mini)
				{
				ALARM_RECEIVED=true;
					ALARM_Hi=false,ALARM_Low=true;
				ALARM_CODE=84;
					return;
				}
//		} 
//		else if(ALARM_ACV_Fr_Maxi < (ACV_RATE+5))
//		{
//			 ALARM_RECEIVED=true;
//			 ALARM_CODE=85;

//		}
		/*else if(ALARM_ACV_FiO2_Mini > (ALARM_ACV_FiO2_Maxi-(ALARM_ACV_FiO2_Maxi*0.1)))
		{
				ALARM_RECEIVED=true;
				ALARM_CODE=86;
			 //create_response_for_raspberry(111,86);
		}
		else if(ALARM_ACV_FiO2_Mini > (ALARM_ACV_FiO2_Maxi-(ALARM_ACV_FiO2_Maxi*0.1)))
		{
			 ALARM_RECEIVED=true;
			 ALARM_CODE=87; 
			//create_response_for_raspberry(111,87);
		}*/
	
		
return;
		
}