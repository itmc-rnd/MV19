#ifndef __ALARMS_SETTING_H
#define __ALARMS_SETTING_H
#endif


#include <main.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

extern int ALARM_PSV_Fr_Maxi,ALARM_PSV_FiO2_Mini,ALARM_PSV_FiO2_Maxi,ALARM_PSV_Vti_Mini,ALARM_PSV_Vti_Maxi,ALARM_PSV_Vte_Mini;
extern int ALARM_ACP_Fr_Maxi,ALARM_ACP_FiO2_Mini,ALARM_ACP_FiO2_Maxi,ALARM_ACP_Vti_Mini,ALARM_ACP_Vti_Maxi,ALARM_ACP_Vte_Mini;
extern int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;
extern int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;

#define MAX_BUFFER_SIZE 500

extern uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];
