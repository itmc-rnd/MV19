#include "pcv_mode.h"
#include "database.h"
#include "driver.h"

extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;
extern int Current_Pressure_Ins,Current_Pressure_Exp;
extern int Current_Flow_Ins,Current_Flow_Exp;

extern float Current_P_Triger;	

extern int t3_counter_old,t3_counter;
extern int pwm_i_pcv, pwm_e_pcv;

int Tt_pcv=0, Ti_pcv=0,  Tflat_pcv=0,Te_pcv=0, trs_step_pcv=100;
int Trs_pcv=0;
int PCV_Ins_Pressure=0, PCV_Exp_Pressure=0, PCV_Vt_Sens=0;
int PCV_Ins_Flow=0, PCV_Exp_Flow=0;

int pwm_max=0;
int pwm_Vt_pcv=0,pwm_Vt_pcv_calulate=0;



void PCV_Mode()
{
	       
   
 	Tt_pcv=6000/PCV_RATE;
	Ti_pcv=(PCV_IT_RATIO * Tt_pcv)/100.0;
	Te_pcv=Tt_pcv - Ti_pcv;
	Trs_pcv=PCV_RISE_TIME*20;
	Tflat_pcv=Ti_pcv-Trs_pcv;
	
	pwm_Vt_pcv=(PCV_Target_Vt/1400.0)*100;
	pwm_max=(PCV_MAXP/55.0)*100;
	pwm_i_pcv=(PCV_IPAP/55.0)*100;
	pwm_e_pcv=(PCV_EPAP/55.0)*100;

  duration_Ins=Ti_pcv;
  duration_Exp=Te_pcv;

//============================ determine IPAP	

if(is_inspiratory==1)
{	
			PCV_Ins_Pressure = Current_Pressure_Ins;
	    PCV_Exp_Pressure = Current_Pressure_Exp;

    	PCV_Ins_Flow = Current_Flow_Exp/1000;  // Flow ins

	
	   PCV_Vt_Sens=(PCV_Vt_Sens + (PCV_Ins_Flow*(t3_counter-t3_counter_old))/100); // determine the volume of breath according to flow
	   t3_counter_old=t3_counter;
	
	  if (PCV_Target_Vt!=0)   // the power of turbo set by volume
    {    
								if(PCV_Ins_Pressure<PCV_MAXP) // The inspiratory pressure should be less than the maximi P
						    {
						
			                 	 if(PCV_Exp_Pressure<=PCV_IPAP)  // for certainty that expiration is Done 
				                 	{  
                               	if((PCV_Vt_Sens-PCV_Target_Vt)<=pwm_Vt_pcv)   // Delet negetive value of pwm
			                             pwm_Vt_pcv_calulate=pwm_Vt_pcv-((PCV_Vt_Sens-PCV_Target_Vt)/1400.0)*100;
			                          
																if(pwm_Vt_pcv_calulate>pwm_Vt_pcv)	
				                           pwm_Vt_pcv_calulate=pwm_Vt_pcv;
	
	                          turbo_speed_Ins=(int)((int)(pwm_Vt_pcv_calulate*198.0)/Ti_pcv);;
	                          duration_Ins=Ti_pcv;
			                			trs_step_pcv=(int)(turbo_speed_Ins-turbo_speed_Exp)/(Trs_pcv);
							          		if (trs_step_pcv==0)
									         	trs_step_pcv=1;
                            raise_step=trs_step_pcv;
														
	                       	}
				                  else
			              			turbo_speed_Ins=14;
				 
			        }		
								else
					  	turbo_speed_Ins=14;
										
			
								
        }						
			else  // the power of turbo set by pressure
			{
			 if(PCV_Exp_Pressure<=PCV_Ins_Pressure)  // for certainty that expiration is Done 
					{  
                	if((PCV_Ins_Pressure-PCV_IPAP)<=pwm_i_pcv)   // Delet negetive value of pwm
			             pwm_i_pcv=pwm_i_pcv-(PCV_Ins_Pressure-PCV_IPAP);
			            else
				           pwm_i_pcv=pwm_i_pcv;
	
	          turbo_speed_Ins=pwm_i_pcv;
	          duration_Ins=Ti_pcv;
						trs_step_pcv=(int)(turbo_speed_Ins-turbo_speed_Exp)/(Trs_pcv);
									if (trs_step_pcv==0)
										trs_step_pcv=1;
            raise_step=trs_step_pcv;
	        	}
				 else
						turbo_speed_Ins=14;
			}	
			
			

		}
//============================ determine EPAP	

if(is_inspiratory==0)
{	
		    
      	PCV_Exp_Pressure = Current_Pressure_Exp;
	
        PCV_Exp_Flow = (-1)*Current_Flow_Exp/1000;	    // Flow Exp
       PCV_Vt_Sens=(PCV_Vt_Sens + PCV_Exp_Flow*t3_counter);  // determine the volume of breath according to flow
	

     	   		if(PCV_Exp_Pressure>=PCV_EPAP)
				   	{
	                if((PCV_Exp_Pressure-PCV_EPAP)>pwm_e_pcv)
			              pwm_e_pcv=pwm_e_pcv-(PCV_Exp_Pressure-PCV_EPAP);
                  else 
		            	 pwm_e_pcv= 0;
					 
		           turbo_speed_Exp=pwm_e_pcv;
	             duration_Exp=Te_pcv;
//							 trs_step=(int)(turbo_speed_Ins-turbo_speed_Exp)/(Trs_pcv1);
	             raise_step=trs_step_pcv;
	    	      }
		    	 else
				   		turbo_speed_Exp=10;
						
}

//	 delay_unit=(Trs/(pwm_max-pwm_min));	

}
    

