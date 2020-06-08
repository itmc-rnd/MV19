#include "acv_alarms.h"
#include "database.h"
#include "check_device_init.h"
#include "stdbool.h"

extern int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Vt;
extern int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;

void ACV_Alarms()
{
	 if(ALARM_ACV_Pi_Mini < (ACV_EPAP+2) || ALARM_ACV_Pi_Mini > (ALARM_ACV_Pi_Maxi-10))
		{
	 create_response_for_raspberry(111,82);
		}
	 else if(ALARM_ACV_Pi_Maxi < (ACV_EPAP+15) || ALARM_ACV_Pi_Maxi <(ALARM_ACV_Pi_Maxi +10))
		{
			 create_response_for_raspberry(111,83);
		} 
		else if(ALARM_ACV_Vte_Mini > ACV_Vt)
		{
			 create_response_for_raspberry(111,84);
		}
		else if(ALARM_ACV_Fr_Maxi < (ACV_RATE+5))
		{
			 create_response_for_raspberry(111,85);
		}
		else if(ALARM_ACV_FiO2_Mini > (ALARM_ACV_FiO2_Maxi-(ALARM_ACV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,86);
		}
		else if(ALARM_ACV_FiO2_Mini > (ALARM_ACV_FiO2_Maxi-(ALARM_ACV_FiO2_Maxi*0.1)))
		{
			 create_response_for_raspberry(111,87);
		}
				else
			return;
		
    return;
		
}