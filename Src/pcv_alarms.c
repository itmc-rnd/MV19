#include "pcv_alarms.h"
#include "database.h"
#include "check_device_init.h"


extern int ACP_IPAP,ACP_EPAP, ACP_RISE_TIME, ACP_RATE, ACP_IT_RATIO, ACP_Inspiratory, ACP_Expiratory,ACP_TRRIG_I,ACP_MAXP,ACP_Target_Vt;
extern int ALARM_ACP_Fr_Maxi,ALARM_ACP_FiO2_Mini,ALARM_ACP_FiO2_Maxi,ALARM_ACP_Vti_Mini,ALARM_ACP_Vti_Maxi,ALARM_ACP_Vte_Mini;


extern bool ALARM_RECEIVED,Audio_Paused_available,Alarm_Paused_available;
extern int ALARM_CODE;
extern bool ALARM_Hi,ALARM_Low;

extern int32_t ACP_Vt_Sens;
float acp_tmp=0.0;

void ACP_Alarms()
{
	 ALARM_RECEIVED=false;
	 acp_tmp=ALARM_ACP_FiO2_Maxi-(ALARM_ACP_FiO2_Maxi*0.1);
	
//	 if(ACP_Target_Vt <= ALARM_ACP_Vti_Mini || ALARM_ACP_Vti_Mini>(ALARM_ACP_Vti_Maxi-50))
//		{
			if(ACP_Vt_Sens<ALARM_ACP_Vti_Mini)
			{
			  ALARM_RECEIVED=true;
				ALARM_Hi=true,ALARM_Low=false;
				
			  Audio_Paused_available=true;
			  Alarm_Paused_available=false;
				
			  ALARM_CODE=70;
				return;
			}  
		
//		}
//	 else if(ACP_Target_Vt >= ALARM_ACP_Vti_Maxi || ALARM_ACP_Vti_Maxi<(ALARM_ACP_Vti_Mini+50))
//		{
			if(ACP_Vt_Sens>ALARM_ACP_Vti_Maxi)
			{
		  	ALARM_RECEIVED=true;
				ALARM_Hi=false,ALARM_Low=true;
			  ALARM_CODE=71;
				return;
			}
		 
	
		//} 
//		else if(ACP_Target_Vt < ALARM_ACP_Vte_Mini)
//		{
			if(ACP_Vt_Sens<ALARM_ACP_Vte_Mini)
			{
			  ALARM_RECEIVED=true;
				ALARM_Hi=false,ALARM_Low=true;
			  ALARM_CODE=72;
				return;
			}
		 
		
	//	}
	//	else if(ALARM_ACP_Fr_Maxi < (ACP_RATE+5))
	//	{
		//  ALARM_RECEIVED=true;
	//		ALARM_CODE=73;
		
	//	}
	/*else if(ALARM_ACP_FiO2_Mini > ((int)tmp))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=74;
		
		}
		else if(ALARM_ACP_FiO2_Mini > ((int)tmp))
		{
		  ALARM_RECEIVED=true;
			ALARM_CODE=75;
	
		}*/
		
    return;
		
}
