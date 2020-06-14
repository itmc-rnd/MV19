#include "acv_mode.h"
#include "database.h"
#include "driver.h"
#include "stdint.h"

extern int ACV_Vt, ACV_EPAP, ACV_RAMP, ACV_RATE, ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory, ACV_TRRIG_I,ACV_Sigh_Rate,ACV_Sigh;
extern float ACV_Vt_Sigh;
extern int is_inspiratory;
extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;
extern int Current_Pressure_Ins,Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern int t3_counter_old,t3_counter,mode_counter;
extern int32_t ACV_Vt_Sens;
extern bool acv_mode_first_round;
extern float Current_P_Triger;	
	
	int32_t ACV_Vt_Sens_Ins=0,ACV_Vt_Sens_Exp=0;
	
int Tt_acv=0, Ttrig_acv=0, Ti_acv=0, Te_acv=0, Tflat_acv=0, delay_unit_acv=0,ACV_Vt_normal=0;
int  ACV_Exp_Pressure=0 ,ACV_Exp_Pressure_normal=0 ,ACV_EPAP_normal=0,  ACV_Ins_Pressure=0 ;
int ACV_Ins_Flow=0, ACV_Exp_Flow=0;
int pwm_Vt_acv=0,pwm_Vt_acv_normal=0 ,pwm_Vt_acv_calulate=0, pwm_e_acv=0,pwm_e_acv_normal=0;
int Pe_Ad_ACV=0, Pe_Pa_ACV=0, Q_Pa_ACV=0, Q_Ad_ACV=0;
float  Pe_ACV= -1.7, Bias_Flow_ACV=20.0,ACV_Exp_Pressure_Trriger=0.0;
extern int sigh_counter;
 
// int ACV_RAMP; 

void ACV_Mode()
{
	
	Tt_acv=6000/ACV_RATE;
	
	Ti_acv=ACV_IT_RATIO*Tt_acv/100;
	Te_acv=Tt_acv-Ti_acv;
	
	pwm_Vt_acv=(ACV_Vt*100)/1400.0;
	pwm_e_acv=(ACV_EPAP*100)/55.0;
	
	Pe_Pa_ACV=Pe_ACV-0.3;
	Pe_Ad_ACV=Pe_ACV-0.3-0.1*ACV_TRRIG_I;
	Q_Pa_ACV=Bias_Flow_ACV+3.5;
	Q_Ad_ACV=Bias_Flow_ACV+4;
	

  duration_Ins=Ti_acv;
  duration_Exp=Te_acv;
	
//============================ determine IPAP	

if(is_inspiratory==1)
{	
			 ACV_Ins_Pressure = Current_Pressure_Ins;
	     ACV_Exp_Pressure = Current_Pressure_Exp;
	
	
      ACV_Ins_Flow=Current_Flow_Ins;     // Flow Ins  
	
      ACV_Vt_Sens=(ACV_Vt_Sens + (ACV_Ins_Flow*(t3_counter-t3_counter_old))/100);	// determine the volume of breath according to flow
	    t3_counter_old=t3_counter;
	     
	     pwm_Vt_acv_normal=(((ACV_Vt_Sens-ACV_Vt)*100)/1400.0);
	   
//  if(ACV_Exp_Pressure<=ACV_Ins_Pressure)  // for certainty that expiration is Done 
//	{  	
	if(ACV_Sigh!=1)  // No sigh
	{
     if (pwm_Vt_acv_normal<=pwm_Vt_acv)     // Delete negetive value of pwm
		    pwm_Vt_acv_calulate=pwm_Vt_acv - pwm_Vt_acv_normal;
											
						    
				if(pwm_Vt_acv_calulate>pwm_Vt_acv)							
              pwm_Vt_acv_calulate=pwm_Vt_acv;																
							  
				turbo_speed_Ins=(int)((int)(pwm_Vt_acv_calulate*198.0)/Ti_acv);
				duration_Ins=Ti_acv;	
				
	}
	else		
	{
		if(sigh_counter<=ACV_Sigh_Rate)  // normal inspiration
		{
						      if (pwm_Vt_acv_normal<=pwm_Vt_acv)     // Delete negetive value of pwm
		          	          pwm_Vt_acv_calulate=pwm_Vt_acv - pwm_Vt_acv_normal;
											
						    
				         	if(pwm_Vt_acv_calulate>pwm_Vt_acv)							
                      pwm_Vt_acv_calulate=pwm_Vt_acv;																
							  
				        	turbo_speed_Ins=(int)((int)(pwm_Vt_acv_calulate*198.0)/Ti_acv);
				        	duration_Ins=Ti_acv;	
											
							  
							  	   sigh_counter=sigh_counter+1;

											
						}
	          else{   // the paitent need the sigh
					     		pwm_Vt_acv_calulate=((ACV_Vt*ACV_Vt_Sigh)*100)/1400.0;
							    sigh_counter=1;
						      turbo_speed_Ins=(pwm_Vt_acv_calulate*198.0)/Ti_acv;
					    		duration_Ins=Ti_acv;
					   		//pwm_Vt_acv=(ACV_Vt/1400)*100;
					      }
	}
				  		
//					}
//					else
//					  	turbo_speed_Ins=14;
 
}


//============================ determine EPAP	

if(is_inspiratory==0)
{	

			ACV_Exp_Pressure=Current_Pressure_Exp;
	    ACV_Exp_Pressure_Trriger=(-1.0)* Current_P_Triger;
    	 ACV_Exp_Flow = (-1)*Current_Flow_Exp;	     // Flow Exp
       ACV_Vt_Sens=(ACV_Vt_Sens + (ACV_Ins_Flow*(t3_counter-t3_counter_old))/100);  // determine the volume of breath according to flow
	     t3_counter_old=t3_counter;
	       pwm_e_acv_normal=(((ACV_Exp_Pressure-ACV_EPAP)*100)/55.0);
	
       if (ACV_TRRIG_I>1)
			 {
				 
			 	 if((ACV_Exp_Flow>Q_Ad_ACV) || (ACV_Exp_Pressure_Trriger<Pe_Ad_ACV))
			       	 {
								 if (pwm_e_acv_normal<=pwm_e_acv)
								       pwm_e_acv=pwm_e_acv -pwm_e_acv_normal ;
									 else
									   	 pwm_e_acv= 15;
					       
								 turbo_speed_Exp=pwm_e_acv;
	               duration_Exp=Te_acv;
									 
					     	 t3_counter=duration_Ins+duration_Exp+1;
			      	 }
							 else
							 {
								 if (pwm_e_acv_normal<=pwm_e_acv)
								     pwm_e_acv=pwm_e_acv - pwm_e_acv_normal;
								 else
									 pwm_e_acv= 15;
	
	          	  turbo_speed_Exp=pwm_e_acv;
	              duration_Exp=Te_acv;
							 }
			 }
			 else if (ACV_TRRIG_I==1)
			 {
			     	 if((ACV_Exp_Flow>Q_Pa_ACV) || (ACV_Exp_Pressure_Trriger<Pe_Pa_ACV))
			      	 {
								 
								if (pwm_e_acv_normal<=pwm_e_acv)
								       pwm_e_acv=pwm_e_acv - pwm_e_acv_normal;
									 else
									   	 pwm_e_acv= 15;
					       
								 turbo_speed_Exp=pwm_e_acv;
	               duration_Exp=Te_acv;
									 
								 t3_counter=duration_Ins+duration_Exp+1;
		     	  	 }
							 else
							 {
								   if (pwm_e_acv_normal<=pwm_e_acv)
								       pwm_e_acv=pwm_e_acv - pwm_e_acv_normal;
									 else
									   	 pwm_e_acv= 15;
	
	          	  turbo_speed_Exp=pwm_e_acv;
	              duration_Exp=Te_acv;
								 }
				 
			 }
			 else
			 {
//			   if(ACV_Exp_Pressure>=ACV_EPAP)
//				   	{
	                if(pwm_e_acv_normal<=pwm_e_acv)
			              pwm_e_acv=pwm_e_acv-pwm_e_acv_normal;
                  else 
		            	 pwm_e_acv= 15;
					 
		           turbo_speed_Exp=pwm_e_acv;
	             duration_Exp=Te_acv;

//	    	      }
//		    	 else
//				   		turbo_speed_Exp=15;
			 }				 			    	
       
}

}   

