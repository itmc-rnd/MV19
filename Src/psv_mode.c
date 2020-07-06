//=====================================================================================
//=================== PSV ST = PRESSURE SUPPORT VENTILATION SPONTANEOUS TIMED ===========
//=====================================================================================

#include "psv_mode.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int PSV_IPAP, PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea, PSV_MAXP, PSV_TRIIG_E, PSV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_Ins, turbo_speed_Exp, raise_step;
extern int Current_Pressure_Ins, Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern int t3_counter, t3_counter_old;
extern float Current_P_Triger;

int Tt_psv = 1000, Ti_psv = 500, Te_psv = 500, Tflat_psv = 0, trs_step_psv = 0, raise_step_psv = 100;
int Tt_psv_apnea, Ti_psv_apnea, Te_psv_apnea, PSV_IT_RATIO_apnea = 33;
int Trs_psv = 0;
int PSV_Ins_Pressure = 0, PSV_Exp_Pressure = 0;
int PSV_Ins_Flow = 0, PSV_Exp_Flow = 0, PSV_Qi_maxi = 0;
int pwm_i_psv = 0, pwm_i_psv_normal = 0, pwm_e_psv = 0, pwm_max_psv = 0;
int Pe_Ad_psv = 0, Pe_Pa_psv = 0, Q_Pa_psv = 0, Q_Ad_psv = 0;
float  Pe_psv = -4.7, Bias_Flow_psv = 20.0, PSV_Exp_Pressure_Trriger = 0.0;
int start_ins_psv_mode = 0, Maxi_Flow = 1;

int PSV_Vt_Sens_normal = 0;
extern int T_expiration;
int is_trigger_psv;

extern int PSV_Flow_MAXi_sens;
extern	int32_t PSV_Vt_Sens;
extern bool PSV_MODE_INS;

int pwm_Vt_psv = 0, pwm_Vt_psv_calulate = 0;
int PSV_Target_Vt_temp = 0;



void PSV_Mode()
{

	Tt_psv_apnea = 6000 / PSV_BUR;
	Ti_psv_apnea = 120; //(PSV_IT_RATIO_apnea * Tt_psv_apnea)/100.0;
	Te_psv_apnea = Tt_psv_apnea - Ti_psv_apnea;

	Trs_psv = PSV_RISE_TIME * 20;

	pwm_Vt_psv = (PSV_Target_Vt / 1400.0) * 100;
	pwm_max_psv = (PSV_MAXP / 55.0) * 100;
	pwm_i_psv = (PSV_IPAP / 55.0) * 100;
	pwm_e_psv = (PSV_EPAP / 55.0) * 100;

	Pe_Pa_psv = Pe_psv - 0.3;
	Pe_Ad_psv = Pe_psv - 0.3 - 0.1 * PSV_TRRIG_I;
	Q_Pa_psv = Bias_Flow_psv + 3.5;
	Q_Ad_psv = Bias_Flow_psv + 4;

	

	
	//============================ Inspiratory Phase


	if (is_inspiratory > 0)
	{
		PSV_Ins_Pressure = Current_Pressure_Ins;
		PSV_Exp_Pressure = Current_Pressure_Exp;
		PSV_Ins_Flow = Current_Flow_Ins;

		PSV_Vt_Sens = (PSV_Vt_Sens + (PSV_Ins_Flow * (t3_counter - t3_counter_old)) / 100);  // determine the volume of breath according to flow
		t3_counter_old = t3_counter;

		if (PSV_BUR == 0) // if Apnea disable
		{

			pwm_i_psv_normal = ((PSV_Ins_Pressure - PSV_IPAP) * 100 / 55.0);

			if (PSV_Target_Vt == 0)
				PSV_Target_Vt_temp = 1400;
			else
				PSV_Target_Vt_temp = PSV_Target_Vt;

			if (PSV_Vt_Sens <= PSV_Target_Vt_temp)
			{

				if (PSV_Ins_Pressure <= PSV_IPAP)   // for certainty that expiration is Done 
				{
					if (pwm_i_psv_normal <= pwm_i_psv)     // Delete negetive value of pwm
						pwm_i_psv = pwm_i_psv - pwm_i_psv_normal;
					else
						pwm_i_psv = pwm_i_psv;

					turbo_speed_Ins = pwm_i_psv;

					trs_step_psv = (int)(turbo_speed_Ins - turbo_speed_Exp) / (Trs_psv);
					if (trs_step_psv == 0)
						trs_step_psv = 1;
					raise_step = trs_step_psv;


					if (PSV_Ins_Flow > PSV_Flow_MAXi_sens)	  // find max ins flow
					{
						PSV_Flow_MAXi_sens = PSV_Ins_Flow;
					}
					else {

						if (PSV_Flow_MAXi_sens > 0)
							if (((PSV_Flow_MAXi_sens - PSV_Ins_Flow) * 100) / PSV_Flow_MAXi_sens >= (-1) * PSV_TRIIG_E)
							{
								turbo_speed_Ins = 12;
								PSV_MODE_INS = false;

							}
					}


				}
				else
				{

					turbo_speed_Ins = 12;
					PSV_MODE_INS = false;
				}
			}
			else
			{
				turbo_speed_Ins = 13;
				PSV_MODE_INS = false;


			}
		}
		else  // ========================================================= if Apnea enable
		{


			PSV_Vt_Sens_normal = ((PSV_Vt_Sens - PSV_Target_Vt) * 100 / 1400.0);
			pwm_i_psv_normal = ((PSV_Ins_Pressure - PSV_IPAP) * 100 / 55.0);

			if (PSV_Target_Vt != 0)   // the power of turbo set by volume
			{



				if (PSV_Vt_Sens < PSV_Target_Vt) // The current volume should be less than the PSV_Target_Vt
				{

					//			                 	 if(PSV_Exp_Pressure<=PSV_IPAP)  // for certainty that expiration is Done 
					//				                 	{  
					if (PSV_Vt_Sens_normal <= pwm_Vt_psv)   // Delete negetive value of pwm
						pwm_Vt_psv_calulate = pwm_Vt_psv - PSV_Vt_Sens_normal;

					if (pwm_Vt_psv_calulate > pwm_Vt_psv)
						pwm_Vt_psv_calulate = pwm_Vt_psv;

					turbo_speed_Ins = (int)((int)(pwm_Vt_psv_calulate * 198.0) / Ti_psv);;

					trs_step_psv = (int)(turbo_speed_Ins - turbo_speed_Exp) / (Trs_psv);
					if (trs_step_psv == 0)
						trs_step_psv = 1;
					raise_step = trs_step_psv;
					if (t3_counter > Ti_psv_apnea)
						PSV_MODE_INS = false;

					//	                       	}
					//				                  else
					//			              			turbo_speed_Ins=14;

				}
				else
				{
					turbo_speed_Ins = 14;
					PSV_MODE_INS = false;
				}


			}
			else  // the power of turbo set by pressure with Apnea
			{
				//			 if(PSV_Exp_Pressure<=PSV_Ins_Pressure)  // for certainty that expiration is Done 
				//					{  
				if (pwm_i_psv_normal <= pwm_i_psv)   // Delete negetive value of pwm
					pwm_i_psv = pwm_i_psv - pwm_i_psv_normal;
				else
					pwm_i_psv = pwm_i_psv;

				turbo_speed_Ins = pwm_i_psv;

				trs_step_psv = (int)(turbo_speed_Ins - turbo_speed_Exp) / (Trs_psv);
				if (trs_step_psv == 0)
					trs_step_psv = 1;
				raise_step = trs_step_psv;
				if (t3_counter > Ti_psv_apnea)
					PSV_MODE_INS = false;

				//	        	}
				//				 else
				//				 {
				//						turbo_speed_Ins=14;
				//				 		PSV_MODE_INS=false;
				//				 }
			}
		}

	}



	//============================ Expiratory Phase

	if (is_inspiratory == 0)
	{


		PSV_Flow_MAXi_sens = 0;
		PSV_Exp_Pressure = Current_Pressure_Exp;
		PSV_Exp_Flow = Current_Flow_Exp;

		PSV_Exp_Pressure_Trriger = (-1.0) * Current_P_Triger;


		if (PSV_TRRIG_I == 1)
		{
			if (/*(PSV_Ins_Flow>Q_Pa_psv) ||*/ (PSV_Exp_Pressure_Trriger < Pe_Pa_psv))
			{
				is_trigger_psv = 1;

				turbo_speed_Ins = pwm_i_psv;

				PSV_MODE_INS = true;
			}
			else
			{
				is_trigger_psv = 0;

				pwm_e_psv = 12;

				turbo_speed_Exp = pwm_e_psv;
				PSV_MODE_INS = false;
				//   duration_Exp=duration_Exp+1;
			}

		}

		else
		{
			if (/*(PSV_Ins_Flow>Q_Ad_psv) || */(PSV_Exp_Pressure_Trriger < Pe_Ad_psv))
			{
				is_trigger_psv = 1;
				turbo_speed_Ins = pwm_i_psv;
				PSV_MODE_INS = true;
			}
			else
			{
				is_trigger_psv = 0;

				pwm_e_psv = 12;

				turbo_speed_Exp = pwm_e_psv;

				PSV_MODE_INS = false;
				// duration_Exp=duration_Exp+1;
			}

		}

		if (PSV_BUR > 0 && T_expiration > (PSV_Apnea * 100) && is_trigger_psv == 0)     // ========================== if Apnea enable
		{
			turbo_speed_Ins = pwm_i_psv;
			PSV_MODE_INS = true;

		}
	}
}
