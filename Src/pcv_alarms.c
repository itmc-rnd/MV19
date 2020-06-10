#include "pcv_alarms.h"
#include "database.h"
#include "check_device_init.h"


extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int ALARM_PCV_Fr_Maxi,ALARM_PCV_FiO2_Mini,ALARM_PCV_FiO2_Maxi,ALARM_PCV_Vti_Mini,ALARM_PCV_Vti_Maxi,ALARM_PCV_Vte_Mini;

<<<<<<< HEAD
int ACV_Ins_Flow=0, ACV_Exp_Flow=0;

extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;
extern int32_t PCV_Vt_Sens;
=======
extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;

>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
float tmp=0.0;

void PCV_Alarms()
{
	 ALARM_RECEIVED=false;
<<<<<<< HEAD
=======
	
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
	 tmp=ALARM_PCV_FiO2_Maxi-(ALARM_PCV_FiO2_Maxi*0.1);
	
	 if(PCV_Target_Vt <= ALARM_PCV_Vti_Mini || ALARM_PCV_Vti_Mini>(ALARM_PCV_Vti_Maxi-50))
		{
<<<<<<< HEAD
			if(PCV_Vt_Sens<ALARM_PCV_Vti_Mini)
			{
			ALARM_RECEIVED=true;
			Audio_Paused_available=true;
			Alarm_Paused_available=false;
			ALARM_CODE=70;
			}  
		//	create_response_for_raspberry(111,70);
		}
	 else if(PCV_Target_Vt >= ALARM_PCV_Vti_Maxi || ALARM_PCV_Vti_Maxi<(ALARM_PCV_Vti_Mini+50))
		{
			if(PCV_Vt_Sens>ALARM_PCV_Vti_Maxi)
			{
			ALARM_RECEIVED=true;
			ALARM_CODE=71;
			}
		 
	//		 create_response_for_raspberry(111,71);
		} 
		else if(PCV_Target_Vt < ALARM_PCV_Vte_Mini)
		{
			if(PCV_Vt_Sens<ALARM_PCV_Vte_Mini)
			{
			ALARM_RECEIVED=true;
			ALARM_CODE=72;
			}
		 
		//	 create_response_for_raspberry(111,72);
=======
			
		  ALARM_RECEIVED=true;
			Audio_Paused_available=true;
			Alarm_Paused_available=false;
			ALARM_CODE=70;

		
		}
	 else if(PCV_Target_Vt >= ALARM_PCV_Vti_Maxi || ALARM_PCV_Vti_Maxi<(ALARM_PCV_Vti_Mini+50))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=71;
	
		} 
		else if(PCV_Target_Vt < ALARM_PCV_Vte_Mini)
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=72;
		
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
		}
		else if(ALARM_PCV_Fr_Maxi < (PCV_RATE+5))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=73;
<<<<<<< HEAD
		//	 create_response_for_raspberry(111,73);
=======
		
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
		}
	/*else if(ALARM_PCV_FiO2_Mini > ((int)tmp))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=74;
<<<<<<< HEAD
		//	 create_response_for_raspberry(111,74);
=======
		
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
		}
		else if(ALARM_PCV_FiO2_Mini > ((int)tmp))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=75;
<<<<<<< HEAD
	//		 create_response_for_raspberry(111,75);
		}*/
=======
	
		}
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
		else
			return;
		
    return;
		
}
