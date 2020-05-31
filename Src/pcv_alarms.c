#include "pcv_alarms.h"
#include "database.h"
#include "check_device_init.h"


extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int ALARM_PCV_Fr_Maxi,ALARM_PCV_FiO2_Mini,ALARM_PCV_FiO2_Maxi,ALARM_PCV_Vti_Mini,ALARM_PCV_Vti_Maxi,ALARM_PCV_Vte_Mini;
/// create_response_for_raspberry(111,alarm_code);

float tmp=0;

void PCV_Alarms()
{
	
	 tmp=ALARM_PCV_FiO2_Maxi-(ALARM_PCV_FiO2_Maxi*0.1);
	
	 if(PCV_Target_Vt <= ALARM_PCV_Vti_Mini || ALARM_PCV_Vti_Mini>(ALARM_PCV_Vti_Maxi-50))
		{
	     create_response_for_raspberry(111,70);
		}
	 else if(PCV_Target_Vt >= ALARM_PCV_Vti_Maxi || ALARM_PCV_Vti_Maxi<(ALARM_PCV_Vti_Mini+50))
		{
			 create_response_for_raspberry(111,71);
		} 
		else if(PCV_Target_Vt < ALARM_PCV_Vte_Mini)
		{
			 create_response_for_raspberry(111,72);
		}
		else if(ALARM_PCV_Fr_Maxi < (PCV_RATE+5))
		{
			 create_response_for_raspberry(111,73);
		}
		else if(ALARM_PCV_FiO2_Mini > ((int)tmp))
		{
			 create_response_for_raspberry(111,74);
		}
		else if(ALARM_PCV_FiO2_Mini > ((int)tmp))
		{
			 create_response_for_raspberry(111,75);
		}
}
