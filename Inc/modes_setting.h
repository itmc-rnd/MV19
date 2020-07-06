#ifndef __MODES_SETTING_H
#define __MODES_SETTING_H
#endif


#include <main.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


extern int PSV_IPAP, PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int ACP_IPAP, ACP_EPAP, ACP_RISE_TIME, ACP_RATE, ACP_IT_RATIO, ACP_Inspiratory, ACP_Expiratory, ACP_TRRIG_I, ACP_MAXP, ACP_Target_Vt;
extern int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Sigh,ACV_Vt;
extern float ACV_Vt_Sigh,ACP_Ti,ACV_Ti,SIMV_Ti;
extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;

#define MAX_BUFFER_SIZE 500

extern uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];
