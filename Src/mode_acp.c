//=====================================================================================
//                               PCV Mode === AC(P) Mode
//=====================================================================================

#include "mode_acp.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int ACP_IPAP, ACP_EPAP, ACP_RISE_TIME, ACP_RATE, ACP_IT_RATIO, ACP_Inspiratory, ACP_Expiratory, ACP_TRRIG_I, ACP_MAXP, ACP_Target_Vt;
extern float ACP_Ti;
extern int is_inspiratory;
extern int turbo_speed_Ins, turbo_speed_Exp, raise_step;
extern int duration_Ins, duration_Exp;
extern int Current_Pressure_Ins, Current_Pressure_Exp;
extern int Current_Flow_Ins, Current_Flow_Exp;

extern float Current_P_Triger;

extern int t3_counter_old, t3_counter;
extern int pwm_i_acp, pwm_e_acp;
extern bool  valve_open;
extern bool wait_for_sycle_finish, wait_for_Ins_finish;

int ACP_Vt_Sens_normal = 0, pwm_i_acp_normal = 0;

int Tt_acp = 0, Ti_acp = 0, Tflat_acp = 0, Te_acp = 0, trs_step_acp = 100;
int Trs_acp = 0;
int ACP_Ins_Pressure = 0, ACP_Exp_Pressure = 0;
extern	int32_t ACP_Vt_Sens;
int ACP_Ins_Flow = 0, ACP_Exp_Flow = 0;
float ACP_Exp_Pressure_Trriger = 0.0;

int pwm_max = 0, pwm_e_acp_normal = 0;
int pwm_Vt_acp = 0, pwm_Vt_acp_calulate = 0;
int Pe_Ad_ACP = 0, Pe_Pa_ACP = 0, Flow_Pa_ACP = 0, Flow_Ad_ACP = 0;
float  Pe_ACP = -1.7, Bias_Flow_ACP = 20.0;



void Mode_ACP()
{


	Tt_acp = 6000 / ACP_RATE;
	Ti_acp = ACP_Ti * 100;//(ACP_IT_RATIO * Tt_acp)/100.0;
	Te_acp = Tt_acp - Ti_acp;
	Trs_acp = ACP_RISE_TIME * 20;
	Tflat_acp = Ti_acp - Trs_acp;

	pwm_Vt_acp = (ACP_Target_Vt / 1400.0) * 100;
	pwm_max = (ACP_MAXP / 55.0) * 100;
	pwm_i_acp = (ACP_IPAP / 55.0) * 100;
	pwm_e_acp = (ACP_EPAP / 55.0) * 100;

	Pe_Pa_ACP = Pe_ACP - 0.3;
	Pe_Ad_ACP = Pe_ACP - 0.3 - 0.1 * ACP_TRRIG_I;
	Flow_Pa_ACP = Bias_Flow_ACP + 3.5;
	Flow_Ad_ACP = Bias_Flow_ACP + 4;

	//============================ Inspiratory Phase	

	if (is_inspiratory == 1)
	{
		ACP_Ins_Pressure = Current_Pressure_Ins;
		ACP_Exp_Pressure = Current_Pressure_Exp;

		ACP_Ins_Flow = Current_Flow_Ins;  // Flow ins

		ACP_Vt_Sens_normal = ((ACP_Vt_Sens - ACP_Target_Vt) * 100 / 1400.0);
		pwm_i_acp_normal = ((ACP_Ins_Pressure - ACP_IPAP) * 100 / 55.0);

		if (ACP_Target_Vt != 0)   // the power of turbo set by volume
		{
			if (wait_for_Ins_finish)
			{
				return;
			}
			else
			{
				if (ACP_Vt_Sens > (ACP_Target_Vt - 50))
				{
					turbo_speed_Ins = pwm_i_acp_normal;
					wait_for_Ins_finish = true;
					return;
				}
			}
			if (ACP_Vt_Sens_normal <= pwm_Vt_acp)   // Delete negetive value of pwm
				pwm_Vt_acp_calulate = pwm_Vt_acp - ACP_Vt_Sens_normal;

			if (pwm_Vt_acp_calulate > pwm_Vt_acp)
				pwm_Vt_acp_calulate = pwm_Vt_acp;

			turbo_speed_Ins = (int)((int)(pwm_Vt_acp_calulate * 198.0) / Ti_acp);;
			duration_Ins = Ti_acp;
			trs_step_acp = (int)(turbo_speed_Ins - turbo_speed_Exp) / (Trs_acp);
			if (trs_step_acp == 0)
				trs_step_acp = 1;
			raise_step = trs_step_acp;


		}
		else  // the power of turbo set by pressure
		{
			if (wait_for_Ins_finish)
			{
				return;
			}
			else
			{
				if (ACP_Ins_Pressure > (ACP_IPAP - 1))
				{
					turbo_speed_Ins = pwm_e_acp;
					wait_for_Ins_finish = true;
					return;
				}
			}

			if (pwm_i_acp_normal <= pwm_i_acp)   // Delete negetive value of pwm
				pwm_i_acp = pwm_i_acp - pwm_i_acp_normal;
			else
				pwm_i_acp = pwm_i_acp;

			turbo_speed_Ins = 2 * pwm_i_acp;
			duration_Ins = Ti_acp;
			trs_step_acp = (int)(turbo_speed_Ins - turbo_speed_Exp) / (Trs_acp);
			if (trs_step_acp == 0)
				trs_step_acp = 1;
			raise_step = trs_step_acp;

		}

	}
	//============================ determine EPAP	

	if (is_inspiratory == 0)
	{

		ACP_Exp_Pressure = Current_Pressure_Exp;
		ACP_Exp_Pressure_Trriger = (-1.0) * Current_P_Triger;

		ACP_Exp_Flow = (-1) * Current_Flow_Exp;	    // Flow Exp

		ACP_Vt_Sens_normal = ((ACP_Vt_Sens - ACP_Target_Vt) * 100 / 1400.0);

		pwm_e_acp_normal = (((ACP_Exp_Pressure - ACP_EPAP) * 100) / 55.0);


		if (ACP_TRRIG_I > 1)
		{

			if ((ACP_Exp_Flow > Flow_Ad_ACP) || (ACP_Exp_Pressure_Trriger < Pe_Ad_ACP))
			{
				if (pwm_e_acp_normal <= pwm_e_acp)
					pwm_e_acp = pwm_e_acp - pwm_e_acp_normal;
				else
					pwm_e_acp = pwm_e_acp;

				turbo_speed_Exp = pwm_e_acp;
				duration_Exp = Te_acp;

				t3_counter = duration_Ins + duration_Exp + 1;
			}
			else
			{
				if (pwm_e_acp_normal <= pwm_e_acp)
					pwm_e_acp = pwm_e_acp - pwm_e_acp_normal;
				else
					pwm_e_acp = pwm_e_acp;

				turbo_speed_Exp = pwm_e_acp;
				duration_Exp = Te_acp;
			}
		}
		else if (ACP_TRRIG_I == 1)
		{
			if ((ACP_Exp_Flow > Flow_Pa_ACP) || (ACP_Exp_Pressure_Trriger < Pe_Pa_ACP))
			{

				if (pwm_e_acp_normal <= pwm_e_acp)
					pwm_e_acp = pwm_e_acp - pwm_e_acp_normal;
				else
					pwm_e_acp = pwm_e_acp;

				turbo_speed_Exp = pwm_e_acp;
				duration_Exp = Te_acp;

				t3_counter = duration_Ins + duration_Exp + 1;
			}
			else
			{
				if (pwm_e_acp_normal <= pwm_e_acp)
					pwm_e_acp = pwm_e_acp - pwm_e_acp_normal;
				else
					pwm_e_acp = pwm_e_acp;

				turbo_speed_Exp = pwm_e_acp;
				duration_Exp = Te_acp;
			}

		}
		else
		{

			if (pwm_e_acp_normal <= pwm_e_acp)
				pwm_e_acp = pwm_e_acp - pwm_e_acp_normal;
			else
				pwm_e_acp = pwm_e_acp;

			turbo_speed_Exp = pwm_e_acp;
			duration_Exp = Te_acp;


		}
		if (wait_for_sycle_finish)
		{

			if (ACP_Exp_Pressure <= (ACP_EPAP - 2))
			{
				turbo_speed_Exp = pwm_e_acp;
				valve_open = false;
				wait_for_sycle_finish = false;
			}
			if (ACP_Exp_Pressure > (ACP_EPAP + 2))
			{
				turbo_speed_Exp = pwm_e_acp;
				valve_open = true;
				wait_for_sycle_finish = false;
			}
		}
		else
		{
			if (ACP_Exp_Pressure * 2 <= (ACP_EPAP))
			{
				turbo_speed_Exp = pwm_e_acp;
				valve_open = false;
				wait_for_sycle_finish = false;
			}
		}
	}


}


