#include "pcv_mode.h"
#include "database.h"
#include "driver.h"

extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_high,turbo_spped_low,raise_step;
extern int duration_high,duration_low;
extern int Current_P1,Current_P2;

int Tt, Ti, Te, Trs, Tflat, delay_unit,trs_step=100;
int PCV_IPAP_Sens, PCV_EPAP_Sens;
extern int pwm_i, pwm_e;
int pwm_max;
	 
void PCV_Mode()
{
	       
   
	Tt=6000/PCV_RATE;
	Ti=(PCV_IT_RATIO*Tt)/100;
	Te=Tt-Ti;
	
	Trs=PCV_RISE_TIME*0.2;
	
	if(turbo_speed_high>=0 && turbo_spped_low>=0)
	{
   	if(turbo_speed_high>turbo_spped_low)
	  {
	     trs_step=(turbo_speed_high-turbo_spped_low)/(Trs);
	  }
  }
	//
		
	
	Tflat=Ti-Trs;
	
	pwm_max=(PCV_MAXP/55.0)*100;
	pwm_i=(PCV_IPAP/55.0)*100;
	pwm_e=(PCV_EPAP/55.0)*100;


//============================ determine IPAP	

if(is_inspiratory==1)
{	
			PCV_IPAP_Sens= Current_P1;
            
     			
			pwm_i=pwm_i-(PCV_IPAP_Sens-PCV_IPAP);
	
	    turbo_speed_high=pwm_i;
	    duration_high=Ti;
	
	
     raise_step=trs_step;
}


//============================ determine EPAP	

if(is_inspiratory==0)
{	
	
	    PCV_IPAP_Sens= Current_P2;           
     			
			pwm_e=pwm_e-(PCV_EPAP_Sens-PCV_EPAP);

		  turbo_spped_low=pwm_e;
	    duration_low=Te;
	
	     raise_step=trs_step;
  
}

//	 delay_unit=(Trs/(pwm_max-pwm_min));	



}
    


