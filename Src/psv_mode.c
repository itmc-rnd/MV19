//=====================================================================================
//=================== PSV ST = PRESSURE SUPPORT VENTILATION SPONTANEOUS TIMED ===========
//=====================================================================================

#include "psv_mode.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int PSV_IPAP,PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;
extern int Current_Pressure_Ins,Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern int t3_counter,t3_counter_old;
extern float Current_P_Triger;	

 int Tt_psv=1000, Ti_psv=500, Te_psv=500, Tflat_psv=0, trs_step_psv=0, raise_step_psv=100;
 int Trs_psv=0;
 int PSV_Ins_Pressure=0, PSV_Exp_Pressure=0;
 int PSV_Ins_Flow=0, PSV_Exp_Flow=0, PSV_Qi_maxi=0;
 int pwm_i_psv=0,pwm_i_psv_normal=0, pwm_e_psv=0, pwm_max_psv=0;
 int Pe_Ad_psv=0, Pe_Pa_psv=0, Q_Pa_psv=0, Q_Ad_psv=0;
 float  Pe_psv= -1.7, Bias_Flow_psv=20.0,PSV_Exp_Pressure_Trriger=0.0;
 int start_ins_psv_mode=0, Maxi_Flow=1, counter_Maxi_Flow=0;

extern int PSV_Flow_MAXi_sens;
extern	int32_t PSV_Vt_Sens;
extern bool PSV_MODE_INS;
 
int PSV_Target_Vt_temp=0;

void PSV_Mode()
{
	     

	Trs_psv=PSV_RISE_TIME*20;
	
	pwm_max_psv=(PSV_MAXP/55.0)*100;
	pwm_i_psv=(PSV_IPAP/55.0)*100;
	pwm_e_psv=(PSV_EPAP/55.0)*100;
	
	Pe_Pa_psv=Pe_psv-0.3;
	Pe_Ad_psv=Pe_psv-0.3-0.1*PSV_TRRIG_I;
	Q_Pa_psv=Bias_Flow_psv+3.5;
	Q_Ad_psv=Bias_Flow_psv+4;

  duration_Ins=Ti_psv;
  duration_Exp=Te_psv;
	
//============================ Inspiratory Phase


   if(is_inspiratory>0)
    {	
		   	PSV_Ins_Pressure= Current_Pressure_Ins;
		    PSV_Exp_Pressure= Current_Pressure_Exp;
        PSV_Ins_Flow=Current_Flow_Exp;      
	
       PSV_Vt_Sens=(PSV_Vt_Sens + (PSV_Ins_Flow*(t3_counter-t3_counter_old))/100);  // determine the volume of breath according to flow
			
			  
			
			pwm_i_psv_normal=((PSV_Ins_Pressure-PSV_IPAP)*100/55.0);  
			
			if(PSV_Target_Vt==0)
				PSV_Target_Vt_temp=1400;
			else
				PSV_Target_Vt_temp=PSV_Target_Vt;
			
			if(PSV_Vt_Sens<=PSV_Target_Vt_temp)
			{
	
        if (PSV_Ins_Pressure<=PSV_IPAP)   // for certainty that expiration is Done 
				   	{  	
	            	if (pwm_i_psv_normal<=pwm_i_psv)     // Delet negetive value of pwm
		              	pwm_i_psv=pwm_i_psv - pwm_i_psv_normal;
	              else
			            	pwm_i_psv=pwm_i_psv;
						
	       turbo_speed_Ins=pwm_i_psv;
	      // duration_Ins=Ti_psv;
       	trs_step_psv=(int)(turbo_speed_Ins-turbo_speed_Exp)/(Trs_psv);
		  	if (trs_step_psv==0)
				  	trs_step_psv=1;
         raise_step=trs_step_psv;

			
         if (PSV_Ins_Flow>PSV_Flow_MAXi_sens)	  // find max ins flow
				 {
					 PSV_Flow_MAXi_sens=PSV_Ins_Flow;
				 }
				 else{
					   counter_Maxi_Flow=t3_counter;
					 if(PSV_Flow_MAXi_sens>0)
					   if(((PSV_Flow_MAXi_sens-PSV_Ins_Flow)*100)/PSV_Flow_MAXi_sens>= (-1)*PSV_TRIIG_E)
				    	  {
						       PSV_MODE_INS=false;
									
					      }
				 }
				 
						
				   	}
			  		else
				  	{
							 PSV_MODE_INS=false;
							 	turbo_speed_Ins=12;
							  duration_Ins=Ti_psv;
				   	}
					}
			else
			{
			      PSV_MODE_INS=false;
						turbo_speed_Ins=13;
						duration_Ins=Ti_psv;
			}
 
   }



//============================ Expiratory Phase

    if(is_inspiratory==0)
      {	
          PSV_Flow_MAXi_sens=0;
				
			    PSV_Exp_Pressure=Current_Pressure_Exp;
	        PSV_Exp_Flow=Current_Flow_Exp;  
	
				PSV_Exp_Pressure_Trriger=(-1.0)* Current_P_Triger;
				
				
         if (PSV_TRRIG_I==1)
			     {
			     	    if(/*(PSV_Ins_Flow>Q_Pa_psv) ||*/ (PSV_Exp_Pressure_Trriger<Pe_Pa_psv))
			         	 {
//					         t3_counter=duration_Ins+duration_Exp+1;
//							  	 start_ins_psv_mode=1;
									 
									 turbo_speed_Ins=pwm_i_psv;
								   PSV_MODE_INS=true;
		     	    	 }
							 else
						  	 {
//								   if ((PSV_Exp_Pressure-PSV_EPAP)>pwm_e_psv)     //  Delete negetive value of pwm
//								       pwm_e_psv=pwm_e_psv - (PSV_Exp_Pressure-PSV_EPAP);
//									 else
									   	 pwm_e_psv= 12;
	                  
	          	  turbo_speed_Exp=pwm_e_psv;
									  PSV_MODE_INS=false;
	           //   duration_Exp=duration_Exp+1;
								 }
				 
			 }
			 
			 else 
			 {
				     	 if(/*(PSV_Ins_Flow>Q_Ad_psv) || */(PSV_Exp_Pressure_Trriger<Pe_Ad_psv))
			       	 {
//					     	 t3_counter=duration_Ins+duration_Exp+1;;
//								 start_ins_psv_mode=1;
								 turbo_speed_Ins=pwm_i_psv;
								 PSV_MODE_INS=true;
			      	 }
							 else
							 {
//								 if ((PSV_Exp_Pressure-PSV_EPAP)>pwm_e_psv)  //   Delete negetive value of pwm
//								     pwm_e_psv=pwm_e_psv - (PSV_Exp_Pressure-PSV_EPAP);
//								 else
									 pwm_e_psv= 12;
	
	          	  turbo_speed_Exp=pwm_e_psv;
								  PSV_MODE_INS=false;
	             // duration_Exp=duration_Exp+1;
							 }
				 
			 }      	
       
    }
	}
  