#include "simv_mode.h"
#include "database.h"
#include "driver.h"

extern int SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV, SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I, SIMV_BUR, SIMV_Apnea, SIMV_Vt;
extern int is_inspiratory;
extern int turbo_speed_high,turbo_spped_low,raise_step;
extern int duration_high,duration_low;
extern int Current_P1,Current_P2, Current_Qi, Current_Qe;
extern int t3_counter;

int Tt_simv, Ttrig_simv, Ti_simv, Te_simv, Tflat_simv, delay_unit_simv;
int SIMV_IPAP_Sens, SIMV_EPAP_Sens;
int SIMV_Qi_Sens, SIMV_Qe_Sens;
 int pwm_i_simv, pwm_e_simv;
 int Pe_Ad, Pe_Pa, Q_Pa, Q_Ad;
 float  Pe= -4.7, Bias_Flow=20.0;
 
// int SIMV_BUR, SIMV_Apnea; 

	
void SIMV_Mode()
{
	      
	
	Tt_simv=6000/SIMV_RATE_SIMV;
	Ttrig_simv= 0.8*Tt_simv;
	Ti_simv=SIMV_IT_RATIO*Tt_simv/100;
	Te_simv=Tt_simv-Ti_simv;
	
	pwm_i_simv=(SIMV_IPAP/55.0)*100;
	pwm_e_simv=(SIMV_EPAP/55.0)*100;
	
	Pe_Pa=Pe-0.3;
	Pe_Ad=Pe-0.3-0.1*SIMV_TRRIG_I;
	Q_Pa=Bias_Flow+3.5;
	Q_Ad=Bias_Flow+4;
	


//============================ determine IPAP	

if(is_inspiratory==1)
{	
			SIMV_IPAP_Sens= Current_P1;
      SIMV_Qi_Sens=Current_Qi;      
	
 if (Current_P2<=SIMV_IPAP)
					{  	
	         	if ((SIMV_IPAP_Sens-SIMV_IPAP)<=pwm_i_simv)
		          	pwm_i_simv=pwm_i_simv - (SIMV_IPAP_Sens-SIMV_IPAP);
	          else
			        	pwm_i_simv=pwm_i_simv;
						
	    turbo_speed_high=pwm_i_simv;
	    duration_high=Ti_simv;
						
					}
					else
							 	turbo_speed_high=10;
 
}


//============================ determine EPAP	

if(is_inspiratory==0)
{	

			SIMV_EPAP_Sens=Current_P2;
	    SIMV_Qe_Sens=Current_Qe;  
	
       if (SIMV_TRRIG_I==1)
			 {
			     	 //if((Ttrig_simv>Tt_simv && SIMV_Qi_Sens>Q_Pa) || (Ttrig_simv>Tt_simv && SIMV_IPAP_Sens>Pe_Pa))
			  	  if(Ttrig_simv>Tt_simv && SIMV_IPAP_Sens>Pe_Pa)
			      	 {
					      t3_counter=0;
								 
//								pwm_e_simv=pwm_e_simv - (SIMV_EPAP_Sens-SIMV_EPAP);
//	
//	          	  turbo_spped_low=pwm_e_simv;
//	              duration_low=Te_simv;
		     	  	 }
							 else
							 {
								   if ((SIMV_EPAP_Sens-SIMV_EPAP)>pwm_e_simv)
								       pwm_e_simv=pwm_e_simv - (SIMV_EPAP_Sens-SIMV_EPAP);
									 else
									   	 pwm_e_simv= 0;
	
	          	  turbo_spped_low=pwm_e_simv;
	              duration_low=Te_simv;
								 }
				 
			 }
			 
			 else 
			 {
				     	 //if((Ttrig_simv>Tt_simv && SIMV_Qi_Sens>Q_Ad) || (Ttrig_simv>Tt_simv && SIMV_IPAP_Sens>Pe_Ad))
				         if(Ttrig_simv>Tt_simv && SIMV_IPAP_Sens>Pe_Ad)
			       	 {
					     	 t3_counter=0;
								 
//								pwm_e_simv=pwm_e_simv - (SIMV_EPAP_Sens-SIMV_EPAP);
//	
//	          	  turbo_spped_low=pwm_e_simv;
//	              duration_low=Te_simv;
			      	 }
							 else
							 {
								 if ((SIMV_EPAP_Sens-SIMV_EPAP)>pwm_e_simv)
								     pwm_e_simv=pwm_e_simv - (SIMV_EPAP_Sens-SIMV_EPAP);
								 else
									 pwm_e_simv= 0;
	
	          	  turbo_spped_low=pwm_e_simv;
	              duration_low=Te_simv;
							 }
				 
			 }      	
       
}

}    