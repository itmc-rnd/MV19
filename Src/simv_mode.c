#include "simv_mode.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV, SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I, SIMV_BUR, SIMV_Apnea, SIMV_Vt;
extern int is_inspiratory;
extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;
extern int Current_Pressure_Ins,Current_Pressure_Exp,Current_Flow_Ins,Current_Flow_Exp;
extern int t3_counter_old,t3_counter;
extern float Current_P_Triger;

 int Tt_simv=0, Ttrig_simv=0, Ti_simv=0, Te_simv=0, Tflat_simv=0, delay_unit_simv=0;
 int SIMV_Ins_Pressure=0, SIMV_Exp_Pressure=0;
 extern int32_t SIMV_Vt_Sens;
 int SIMV_Ins_Flow=0, SIMV_Exp_Flow=0;
 int pwm_i_simv=0,pwm_Vt_simv_normal=0, pwm_e_simv=0,pwm_i_simv_normal=0,pwm_e_simv_normal=0;
 int Pe_Ad_SIMV=0, Pe_Pa_SIMV=0, Q_Pa_SIMV=0, Q_Ad_SIMV=0;
 float  Pe= +1.7, Bias_Flow=20.0,SIMV_Exp_Pressure_Trriger=0.0;
 
 extern  int is_trigger;
 
int pwm_Vt_simv=0,pwm_Vt_simv_calulate=0;

// int SIMV_BUR, SIMV_Apnea; 

	
void SIMV_Mode()
{
	
	Tt_simv=6000/SIMV_RATE_SIMV;
	Ttrig_simv= (80*Tt_simv)/100;
	Ti_simv=SIMV_IT_RATIO*Tt_simv/100;
	Te_simv=Tt_simv-Ti_simv;
	
	pwm_i_simv=(SIMV_IPAP/55.0)*100;
	pwm_e_simv=(SIMV_EPAP/55.0)*100;
	
	pwm_Vt_simv=(SIMV_Vt/1400.0)*100;
	
	Pe_Pa_SIMV=Pe+0.3;
	Pe_Ad_SIMV=Pe+0.3+0.1*SIMV_TRRIG_I;
	Q_Pa_SIMV=Bias_Flow+3.5;
	Q_Ad_SIMV=Bias_Flow+4;
	

  duration_Ins=Ti_simv;
  duration_Exp=Te_simv;

	
//============================ determine IPAP	
 

if(is_inspiratory==1)
{	
			SIMV_Ins_Pressure= Current_Pressure_Ins;
	    SIMV_Exp_Pressure=Current_Pressure_Exp;
      SIMV_Ins_Flow=Current_Flow_Exp;        // Flow Ins 
	    

	
	   SIMV_Vt_Sens=(SIMV_Vt_Sens + (SIMV_Ins_Flow*(t3_counter-t3_counter_old))/100); // determine the volume of breath according to flow
	   t3_counter_old=t3_counter;
	
		     pwm_Vt_simv_normal=(((SIMV_Vt_Sens-SIMV_Vt)*100)/1400.0);
	     pwm_i_simv_normal=((SIMV_Ins_Pressure-SIMV_IPAP)*100/55.0);
	
	  if (SIMV_Vt!=0)   // the power of turbo set by volume
    {    
								if(SIMV_Vt_Sens<SIMV_Vt) // The current volume should be less than the SIMV_Vt
						    {
						
			                 	 
                               	if(pwm_Vt_simv_normal<=pwm_Vt_simv)   // Delet negetive value of pwm
			                             pwm_Vt_simv_calulate=pwm_Vt_simv-pwm_Vt_simv_normal;
			                          
																if(pwm_Vt_simv_calulate>pwm_Vt_simv)	
				                           pwm_Vt_simv_calulate=pwm_Vt_simv;
	
	                          turbo_speed_Ins=(int)((int)(pwm_Vt_simv_calulate*198.0)/Ti_simv);;
	                          duration_Ins=Ti_simv;			                															                      
				 
			        }		
								else
					  	    turbo_speed_Ins=14;
										
			
								
        }						
			else  // the power of turbo set by pressure
			{
			 if(SIMV_Ins_Pressure<SIMV_IPAP)  //  The current pressure should be less than the SIMV_IPAP
					{  
                	if(pwm_i_simv_normal<=pwm_i_simv)   // Delet negetive value of pwm
			             pwm_i_simv=pwm_i_simv-pwm_i_simv_normal;
			            else
				           pwm_i_simv=pwm_i_simv;
	
	          turbo_speed_Ins=pwm_i_simv;
	          duration_Ins=Ti_simv;
	
	        	}
				 else
						turbo_speed_Ins=14;
			}	
 
}


//============================ determine EPAP	

if(is_inspiratory==0)
{	

			 SIMV_Exp_Pressure=Current_Pressure_Exp;
	     SIMV_Exp_Pressure_Trriger= Current_P_Triger;
    	 SIMV_Exp_Flow = (-1)*Current_Flow_Exp;	     // Flow Exp
  
      SIMV_Vt_Sens=(SIMV_Vt_Sens + (SIMV_Exp_Flow*(t3_counter-t3_counter_old))/100);  // determine the volume of breath according to flow
	    pwm_e_simv_normal=((SIMV_Exp_Pressure-SIMV_EPAP)*100/55.0); 
	
	
	     t3_counter_old=t3_counter;
	
       if (SIMV_TRRIG_I>1)
			 {
				 
//			 	  if(SIMV_Exp_Pressure<SIMV_EPAP)  //  The current pressure should be less than the SIMV_EPAP
//				 {
					 if(((t3_counter>Ttrig_simv) && (SIMV_Exp_Flow>Q_Ad_SIMV)) || ((t3_counter>Ttrig_simv) && (SIMV_Exp_Pressure_Trriger>Pe_Ad_SIMV)))
			       	 {
								  is_trigger=2;
								 if (pwm_e_simv_normal<=pwm_e_simv)
								       pwm_e_simv=pwm_e_simv - pwm_e_simv_normal;
									 else
									   	 pwm_e_simv= 15;
					       
								 turbo_speed_Exp=pwm_e_simv;
	               duration_Exp=Te_simv;
									 
					     	 t3_counter=duration_Ins+duration_Exp+1;
			      	 }
							 else
							 {
								 if (pwm_e_simv_normal<=pwm_e_simv)
								     pwm_e_simv=pwm_e_simv - pwm_e_simv_normal;
								 else
									 pwm_e_simv= 15;
	
	          	  turbo_speed_Exp=pwm_e_simv;
	              duration_Exp=Te_simv;
							 }				 
//			 }				 
//		    	 else
//				   		turbo_speed_Exp=15;
			 }
			 else if (SIMV_TRRIG_I==1)
			 {
				 
//				 if(SIMV_Exp_Pressure<SIMV_EPAP)  //  The current pressure should be less than the SIMV_EPAP
//				 {
			     	 if(((t3_counter>Ttrig_simv) && (SIMV_Exp_Flow>Q_Pa_SIMV)) || ((t3_counter>Ttrig_simv) && (SIMV_Exp_Pressure_Trriger>Pe_Pa_SIMV)))
			      	 {
								 is_trigger=1;
								if (pwm_e_simv_normal<=pwm_e_simv)
								       pwm_e_simv=pwm_e_simv - pwm_e_simv_normal;
									 else
									   	 pwm_e_simv= 15;
					       
								 turbo_speed_Exp=pwm_e_simv;
	               duration_Exp=Te_simv;
									 
								 t3_counter=duration_Ins+duration_Exp+1;
		     	  	 }
							 else
							 {
								   if (pwm_e_simv_normal<=pwm_e_simv)
								       pwm_e_simv=pwm_e_simv - pwm_e_simv_normal;
									 else
									   	 pwm_e_simv= 15;
	
	          	  turbo_speed_Exp=pwm_e_simv;
	              duration_Exp=Te_simv;
								 }
//							 }				 
//		    	 else
//				   		turbo_speed_Exp=15;
				 
			 }
			 else
			 {
				  is_trigger=-1;
//			   if(SIMV_Exp_Pressure<SIMV_EPAP)  //  The current pressure should be less than the SIMV_EPAP
//				   	{
	                if(pwm_e_simv_normal<=pwm_e_simv)
			              pwm_e_simv=pwm_e_simv-pwm_e_simv_normal;
                  else 
		            	 pwm_e_simv= 15;
					 
		           turbo_speed_Exp=pwm_e_simv;
	             duration_Exp=Te_simv;

//	    	      }
//		    	 else
//				   		turbo_speed_Exp=15;
			 }				 			    	
       
}

}   
