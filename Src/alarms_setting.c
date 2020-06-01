#include "alarms_setting.h"


// BEGIN OF ALARMS Packet DECODER

void psv_alarm_decoder()
{
		     ALARM_PSV_Fr_Maxi=rspy_receive_buffer[4];
	       ALARM_PSV_FiO2_Mini=rspy_receive_buffer[5];
				 ALARM_PSV_FiO2_Maxi=rspy_receive_buffer[6];
				 ALARM_PSV_Vti_Mini=rspy_receive_buffer[7]*16+rspy_receive_buffer[8];
				 ALARM_PSV_Vti_Maxi=rspy_receive_buffer[9]*16+rspy_receive_buffer[10];
				 ALARM_PSV_Vte_Mini=rspy_receive_buffer[11]*16+rspy_receive_buffer[12];			   
  
}
void pcv_alarm_decoder()
{
		     ALARM_PCV_Fr_Maxi=rspy_receive_buffer[4];
	       ALARM_PCV_FiO2_Mini=rspy_receive_buffer[5];
				 ALARM_PCV_FiO2_Maxi=rspy_receive_buffer[6];
				 ALARM_PCV_Vti_Mini=rspy_receive_buffer[7]*16+rspy_receive_buffer[8];
				 ALARM_PCV_Vti_Maxi=rspy_receive_buffer[9]*16+rspy_receive_buffer[10];
				 ALARM_PCV_Vte_Mini=rspy_receive_buffer[11]*16+rspy_receive_buffer[12];
  
}
void acv_alarm_decoder()
{
		     ALARM_ACV_Pi_Mini=rspy_receive_buffer[4];
	       ALARM_ACV_Pi_Maxi=rspy_receive_buffer[5];
				 ALARM_ACV_Fr_Maxi=rspy_receive_buffer[6];
				 ALARM_ACV_FiO2_Mini=rspy_receive_buffer[7];
				 ALARM_ACV_FiO2_Maxi=rspy_receive_buffer[8];
				 ALARM_ACV_Vte_Mini=rspy_receive_buffer[9]*16+rspy_receive_buffer[10];
			   
  
}
void simv_alarm_decoder()
{
		     ALARM_SIMV_Pi_Mini=rspy_receive_buffer[4];
	       ALARM_SIMV_Pi_Maxi=rspy_receive_buffer[5];
				 ALARM_SIMV_Fr_Maxi=rspy_receive_buffer[6];
				 ALARM_SIMV_FiO2_Mini=rspy_receive_buffer[7];
				 ALARM_SIMV_FiO2_Maxi=rspy_receive_buffer[8];
				 ALARM_SIMV_Vte_Mini=rspy_receive_buffer[9]*16+rspy_receive_buffer[10];
			   
  
}

// END OF ALARMS Packet DECODER

