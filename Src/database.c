#include "database.h"
#include "stdint.h"

bool turbo_error = false, pressure_s1_error = false, pressure_s2_error = false, buzzer_error = false, flow_s1_error = false, flow_s2_error = false;

bool data_received_from_raspy = false;

modes CURRENT_MODE;

int pressure_sensor_Ins = 1, pressure_sensor_Exp = 2, pressure_sensor_Triger = 3, flow_sensor_Ins = 2, flow_sensor_Exp = 1;

int PSV_IPAP, PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea, PSV_MAXP, PSV_TRIIG_E, PSV_Target_Vt;

int ACP_IPAP, ACP_EPAP, ACP_RISE_TIME, ACP_RATE, ACP_IT_RATIO, ACP_Inspiratory, ACP_Expiratory, ACP_TRRIG_I, ACP_MAXP, ACP_Target_Vt;

int ACV_EPAP, ACV_RAMP, ACV_RATE, ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory, ACV_TRRIG_I, ACV_Sigh_Rate, ACV_Sigh, ACV_Vt;
float ACV_Vt_Sigh,ACP_Ti, ACV_Ti, SIMV_Ti;
int SIMV_IPAP, SIMV_EPAP, SIMV_RATE_SIMV, SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory, SIMV_TRRIG_I, SIMV_BUR, SIMV_Apnea, SIMV_Vt;

int ALARM_PSV_Fr_Maxi, ALARM_PSV_FiO2_Mini, ALARM_PSV_FiO2_Maxi, ALARM_PSV_Vti_Mini, ALARM_PSV_Vti_Maxi, ALARM_PSV_Vte_Mini;
int ALARM_ACP_Fr_Maxi, ALARM_ACP_FiO2_Mini, ALARM_ACP_FiO2_Maxi, ALARM_ACP_Vti_Mini, ALARM_ACP_Vti_Maxi, ALARM_ACP_Vte_Mini;
int ALARM_ACV_Pi_Mini, ALARM_ACV_Pi_Maxi, ALARM_ACV_Fr_Maxi, ALARM_ACV_FiO2_Mini, ALARM_ACV_FiO2_Maxi, ALARM_ACV_Vte_Mini;
int ALARM_SIMV_Pi_Mini, ALARM_SIMV_Pi_Maxi, ALARM_SIMV_Fr_Maxi, ALARM_SIMV_FiO2_Mini, ALARM_SIMV_FiO2_Maxi, ALARM_SIMV_Vte_Mini;

char buf[500];

int Current_IPAP, Current_EPAP, Current_Apnea;

int turbo_speed_Ins = 0, turbo_speed_Exp = 0, raise_step = 100;
int duration_Ins = 500, duration_Exp = 500;
int is_inspiratory = 1, turbo_speed = 0;
int pwm_i_acp, pwm_e_acp;

int  st[20], Current_Pressure_Ins = 0, Current_Pressure_Exp = 0, Current_Flow_Ins = 0, Current_Flow_Exp = 0;
int Pressure_Report = 0, Flow_Report = 0, Voloume_Report = 0, PasOxi_Report = 0, O2_Report = 0;
bool send_report = false;

float Current_P_Triger = 0.0;

bool Config_request = false, status_change_falg = false;

int status_bar = 14;

int32_t ACV_Vt_Sens = 0, ACP_Vt_Sens = 0, SIMV_Vt_Sens = 0, PSV_Vt_Sens = 0;

int flow_to_voloume_des = 50;

int32_t ACV_Vt_Sens_Ins = 0, ACV_Vt_Sens_Exp = 0;
int32_t ACP_Vt_Sens_Ins = 0, ACP_Vt_Sens_Exp = 0;
int32_t PSV_Vt_Sens_Ins = 0, PSV_Vt_Sens_Exp = 0;
int32_t SIMV_Vt_Sens_Ins = 0, SIMV_Vt_Sens_Exp = 0;

int t3_counter_old = 0, t3_counter = 0, mode_counter = 0;
int  T_expiration = 0, T_expiration_simv = 0;

bool ALARM_RECEIVED = false, Audio_Paused_available = false, Alarm_Paused_available = false;
int ALARM_CODE = 0;

bool acv_mode_first_round = true;

int PSV_Flow_MAXi_sens = 0;

bool PSV_MODE_INS=false;
int PSV_MODE_STEP = 2;  // 0=EXP , 1=Ins , 2=cycle start

bool sigh_occured=false;
int sigh_counter = 0;

int cnt_temp = 0;


int is_trigger_simv = 0;
int is_apnea_simv = 0;
bool  valve_open = false;

uint8_t report_response_packet[148];
int report_response_packet_index = 0;
int packet_index = 0;

bool wait_for_sycle_finish = false, wait_for_Ins_finish = false;


