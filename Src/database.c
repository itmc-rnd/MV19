#include "database.h"
#include "stdint.h"

bool turbo_error=false,pressure_s1_error=false,pressure_s2_error=false,buzzer_error=false,flow_s1_error=false,flow_s2_error=false;

modes CURRENT_MODE;

int PSV_IPAP,PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
int ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Vt;
float ACV_Vt_Sigh;
int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt;

int ALARM_PSV_Fr_Maxi,ALARM_PSV_FiO2_Mini,ALARM_PSV_FiO2_Maxi,ALARM_PSV_Vti_Mini,ALARM_PSV_Vti_Maxi,ALARM_PSV_Vte_Mini;
int ALARM_PCV_Fr_Maxi,ALARM_PCV_FiO2_Mini,ALARM_PCV_FiO2_Maxi,ALARM_PCV_Vti_Mini,ALARM_PCV_Vti_Maxi,ALARM_PCV_Vte_Mini;
int ALARM_ACV_Pi_Mini,ALARM_ACV_Pi_Maxi,ALARM_ACV_Fr_Maxi,ALARM_ACV_FiO2_Mini,ALARM_ACV_FiO2_Maxi,ALARM_ACV_Vte_Mini;
int ALARM_SIMV_Pi_Mini,ALARM_SIMV_Pi_Maxi,ALARM_SIMV_Fr_Maxi,ALARM_SIMV_FiO2_Mini,ALARM_SIMV_FiO2_Maxi,ALARM_SIMV_Vte_Mini;

char buf[500];

int Current_IPAP,Current_EPAP,Current_Apnea;

int turbo_speed_Ins=0,turbo_speed_Exp=0,raise_step=100;
int duration_Ins=500,duration_Exp=500;
int is_inspiratory=1,turbo_speed=0;
int pwm_i_pcv, pwm_e_pcv;

int  st[20],Current_Pressure_Ins=0,Current_Pressure_Exp=0,Current_Flow_Ins=0,Current_Flow_Exp=0;

float Current_P_Triger=0.0;

bool Config_request=false,status_change_falg=false;

int status_bar=7;

int32_t ACV_Vt_Sens=10,PCV_Vt_Sens=0,SIMV_Vt_Sens=0;

int t3_counter_old=0,t3_counter=0,mode_counter=0;

bool ALARM_RECEIVED=false,Audio_Paused_available=false,Alarm_Paused_available=false;
int ALARM_CODE=0;

bool acv_mode_first_round=true;

int PSV_Flow_MAXi_sens=0;

bool PSV_MODE_INS=false;



