#ifndef __MODES_SETTING_H
#define __MODES_SETTING_H


#include "stdint.h"
#include <string.h>
#include <database.h>


extern int PSV_IPAP, PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_MAXP,ACV_Sigh_Rate,ACV_Vt;
extern float ACV_Vt_Sigh;
extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;


extern uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];

#endif
