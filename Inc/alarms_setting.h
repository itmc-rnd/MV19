#ifndef __ALARMS_SETTING_H
#define __ALARMS_SETTING_H

#include "stdint.h"
#include <string.h>
#include <database.h>

extern int ALARM_PSV_Fr_Maxi,ALARM_PSV_FiO2_Mini,ALARM_PSV_FiO2_Maxi,ALARM_PSV_Vti_Mini,ALARM_PSV_Vti_Maxi,ALARM_PSV_Vte_Mini;
extern int ALARM_PCV_Fr_Maxi,ALARM_PCV_FiO2_Mini,ALARM_PCV_FiO2_Maxi,ALARM_PCV_Vti_Mini,ALARM_PCV_Vti_Maxi,ALARM_PCV_Vte_Mini;
extern int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;
extern int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;


extern uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];

#endif
