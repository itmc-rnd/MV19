#include "simv_mode.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int SIMV_IPAP, SIMV_EPAP, SIMV_RATE_SIMV, SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory, SIMV_TRRIG_I, SIMV_BUR, SIMV_Apnea, SIMV_Vt;
extern float SIMV_Ti;
extern int is_inspiratory;
extern int turbo_speed_Ins, turbo_speed_Exp, raise_step;
extern int duration_Ins, duration_Exp;
extern int Current_Pressure_Ins, Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern int t3_counter_old, t3_counter;
extern float Current_P_Triger;
extern bool  valve_open;
extern bool wait_for_sycle_finish, wait_for_Ins_finish;

int Tt_simv = 0, Ttrig_simv = 0, Ti_simv = 0, Te_simv = 0, Tflat_simv = 0, delay_unit_simv = 0;
int Tt_simv_apnea = 0, Ti_simv_apnea = 0, Te_simv_apnea = 0;
int SIMV_Ins_Pressure = 0, SIMV_Exp_Pressure = 0;
extern int32_t SIMV_Vt_Sens;
int SIMV_Ins_Flow = 0, SIMV_Exp_Flow = 0;
int pwm_i_simv = 0, pwm_Vt_simv_normal = 0, pwm_e_simv = 0, pwm_i_simv_normal = 0, pwm_e_simv_normal = 0;
int Pe_Ad_SIMV = 0, Pe_Pa_SIMV = 0, Q_Pa_SIMV = 0, Q_Ad_SIMV = 0;
float  Pe = +1.7, Bias_Flow = 20.0, SIMV_Exp_Pressure_Trriger = 0.0;

extern  int is_trigger_simv;
extern int T_expiration_simv;
extern int is_apnea_simv;

int pwm_Vt_simv = 0, pwm_Vt_simv_calulate = 0;

// int SIMV_BUR, SIMV_Apnea; 


void SIMV_Mode()
{

	Tt_simv_apnea = 6000 / SIMV_BUR;
	Ti_simv_apnea = SIMV_Ti * 100;;
	Te_simv_apnea = Tt_simv_apnea - Ti_simv_apnea;

	Tt_simv = 6000 / SIMV_RATE_SIMV;
	Ttrig_simv = (80 * Tt_simv) / 100;
	Ti_simv = SIMV_Ti * 100;//SIMV_IT_RATIO*Tt_simv/100;
	Te_simv = Tt_simv - Ti_simv;

	pwm_i_simv = (SIMV_IPAP / 55.0) * 100;
	pwm_e_simv = (SIMV_EPAP / 55.0) * 100;

	pwm_Vt_simv = (SIMV_Vt / 1400.0) * 100;

	Pe_Pa_SIMV = Pe + 0.3;
	Pe_Ad_SIMV = Pe + 0.3 + 0.1 * SIMV_TRRIG_I;
	Q_Pa_SIMV = Bias_Flow + 3.5;
	Q_Ad_SIMV = Bias_Flow + 4;


	//============================ determine IPAP	


	if (is_inspiratory == 1)
	{
		SIMV_Ins_Pressure = Current_Pressure_Ins;
		SIMV_Ins_Flow = Current_Flow_Ins;        // Flow Ins 

		pwm_Vt_simv_normal = (((SIMV_Vt_Sens - SIMV_Vt) * 100) / 1400.0);
		pwm_i_simv_normal = ((SIMV_Ins_Pressure - SIMV_IPAP) * 100 / 55.0);

		if (is_apnea_simv != 0)   // if Apnea occured
		{
			if (wait_for_Ins_finish)
			{
				return;
			}
			else
			{
				if (SIMV_Vt_Sens > (SIMV_Vt - 50))
				{
					turbo_speed_Ins = pwm_i_simv_normal;
					wait_for_Ins_finish = true;
					return;
				}
			}
				if (pwm_Vt_simv_normal <= pwm_Vt_simv)   // Delete negetive value of pwm
					pwm_Vt_simv_calulate = pwm_Vt_simv - pwm_Vt_simv_normal;

				if (pwm_Vt_simv_calulate > pwm_Vt_simv)
					pwm_Vt_simv_calulate = pwm_Vt_simv;

				turbo_speed_Ins = (int)((int)(pwm_Vt_simv_calulate * 198.0) / Ti_simv);;
				duration_Ins = Ti_simv_apnea;
        duration_Exp = Te_simv;   


		}
		else   // if Apnea dont occured
		{
			
//			if (wait_for_Ins_finish)
//			{
//				return;
//			}
//			else
//			{
//				if (SIMV_Ins_Pressure > (SIMV_IPAP - 1))
//				{
//					turbo_speed_Ins = pwm_e_simv;
//					wait_for_Ins_finish = true;
//					return;
//				}
//			}
			if (wait_for_Ins_finish)
			{
				return;
			}
			else
			{
				if (SIMV_Vt_Sens > (SIMV_Vt - 50))
				{
					turbo_speed_Ins = pwm_i_simv_normal;
					wait_for_Ins_finish = true;
					return;
				}
			}
				if (pwm_i_simv_normal <= pwm_i_simv)   // Delete negetive value of pwm
					pwm_i_simv = pwm_i_simv - pwm_i_simv_normal;
				else
					pwm_i_simv = pwm_i_simv;

				turbo_speed_Ins = pwm_i_simv;
				duration_Ins = Ti_simv;
        duration_Exp = Te_simv;

		}

	}


	//============================ determine EPAP	

	if (is_inspiratory == 0)
	{

		SIMV_Exp_Pressure = Current_Pressure_Exp;
		SIMV_Exp_Pressure_Trriger = Current_P_Triger;
		SIMV_Exp_Flow = (-1) * Current_Flow_Exp;	     // Flow Exp

		pwm_e_simv_normal = ((SIMV_Exp_Pressure - SIMV_EPAP) * 100 / 55.0);


		t3_counter_old = t3_counter;

		if (SIMV_TRRIG_I > 1)
		{
			if (((SIMV_Exp_Flow > Q_Ad_SIMV) || (SIMV_Exp_Pressure_Trriger > Pe_Ad_SIMV)))
			{
				is_trigger_simv = 1;


				if ((t3_counter > Ttrig_simv))
				{
					if (pwm_e_simv_normal <= pwm_e_simv)
						pwm_e_simv = pwm_e_simv - pwm_e_simv_normal;
					else
						pwm_e_simv = pwm_e_simv;


					duration_Exp = Te_simv;
					duration_Ins = Ti_simv;
					turbo_speed_Exp = pwm_e_simv;

					t3_counter = duration_Ins + duration_Exp + 1;
				}
			}
			else
			{
				is_trigger_simv = 0;
				if (pwm_e_simv_normal <= pwm_e_simv)
					pwm_e_simv = pwm_e_simv - pwm_e_simv_normal;
				else
					pwm_e_simv = pwm_e_simv;

				turbo_speed_Exp = pwm_e_simv;
				duration_Exp = Te_simv;
				duration_Ins = Ti_simv;
			}

		}
		else if (SIMV_TRRIG_I == 1)
		{
			if ((((SIMV_Exp_Flow > Q_Pa_SIMV)) || (SIMV_Exp_Pressure_Trriger > Pe_Pa_SIMV)))
			{

				is_trigger_simv = 1;

				if ((t3_counter > Ttrig_simv))
				{

					if (pwm_e_simv_normal <= pwm_e_simv)
						pwm_e_simv = pwm_e_simv - pwm_e_simv_normal;
					else
						pwm_e_simv = pwm_e_simv;


					duration_Exp = Te_simv;
					duration_Ins = Ti_simv;
					t3_counter = duration_Ins + duration_Exp + 1;
					turbo_speed_Exp = 25;//pwm_e_simv;

				}
			}
			else
			{
				is_trigger_simv = 0;
				if (pwm_e_simv_normal <= pwm_e_simv)
					pwm_e_simv = pwm_e_simv - pwm_e_simv_normal;
				else
					pwm_e_simv = pwm_e_simv;


				duration_Exp = Te_simv;
				duration_Ins = Ti_simv;
				turbo_speed_Exp = pwm_e_simv;
			}

		}


		if (T_expiration_simv > (SIMV_Apnea * 100) && is_trigger_simv == 0)     // ========================== if Apnea enable
		{


			turbo_speed_Ins = pwm_Vt_simv;
			duration_Ins = Ti_simv_apnea;
			duration_Exp = Te_simv_apnea;
			is_apnea_simv = 1;
			t3_counter = duration_Ins + duration_Exp + 1;
		}

		if (wait_for_sycle_finish)
		{

			if (SIMV_Exp_Pressure <= (SIMV_EPAP - 2))
			{
				turbo_speed_Exp = pwm_e_simv;
				valve_open = false;
				wait_for_sycle_finish = false;
			}
			if (SIMV_Exp_Pressure > (SIMV_EPAP + 2))
			{
				turbo_speed_Exp = pwm_e_simv;
				valve_open = true;
				wait_for_sycle_finish = false;
			}
		}
		else
		{
			if (SIMV_Exp_Pressure * 2 <= (SIMV_EPAP))
			{
				turbo_speed_Exp = pwm_e_simv;
				valve_open = false;
				wait_for_sycle_finish = false;
			}
		}
	}

}
