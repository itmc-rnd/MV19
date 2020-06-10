#include "acv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Vt;
extern int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;
float tmp=0.0;

int  ACV_Ins_Pressure=0 ;
extern int Current_P1,Current_P2, Current_F1, Current_F2,t3_counter;
int ACV_Ins_Flow=0, ACV_Exp_Flow=0,Sum=0,avg=0;
int32_t ACV_Vt_Sens_Ins=0,ACV_Vt_Sens_Exp=0;
extern int32_t ACV_Vt_Sens;
extern int t3_counter_old,t3_counter;
int Tt_acv;
float Fr;

void ACV_Alarms()
{
			ACV_Ins_Pressure = Current_P1;
			Tt_acv=6000/ACV_RATE;
			
	if(t3_counter<3)
				{ 
					Fr=1/Tt_acv;
					Sum=Fr+Fr;
					t3_counter++;
				}
		avg=Sum/3;
	 if(ALARM_ACV_Pi_Mini < (ACV_EPAP+2) || ALARM_ACV_Pi_Mini > (ALARM_ACV_Pi_Maxi-10))
		{
			if(Current_P1<ALARM_ACV_Pi_Mini)
				{
					ALARM_RECEIVED=true;
					ALARM_CODE=82;
					//create_response_for_raspberry(111,82);
				}
				else if(ALARM_ACV_Pi_Maxi<Current_P1)
				{
					ALARM_RECEIVED=true;
					ALARM_CODE=83;
					// create_response_for_raspberry(111,83);
				}
		}
	 else if(ALARM_ACV_Pi_Maxi < (ACV_EPAP+15) || ALARM_ACV_Pi_Maxi <(ALARM_ACV_Pi_Maxi +10))
		{
				if(ACV_Vt_Sens<ALARM_ACV_Vte_Mini)
				{
				ALARM_RECEIVED=true;
				ALARM_CODE=84;
				// create_response_for_raspberry(111,83);
				}
		} 
		else if(ALARM_ACV_Fr_Maxi < (ACV_RATE+5))
		{
			 ALARM_RECEIVED=true;
			 ALARM_CODE=85;
			//create_response_for_raspberry(111,85);
		}
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
				else
			return;
		
    return;
		
}