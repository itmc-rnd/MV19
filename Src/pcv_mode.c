#include "pcv_mode.h"
#include "database.h"
#include "driver.h"

extern int PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_high,turbo_spped_low,raise_step;
extern int duration_high,duration_low;
extern int Current_P1,Current_P2;

int Tt_pcv, Ti_pcv, Te_pcv, Tflat_pcv, delay_unit_pcv,trs_step=100;
int PCV_IPAP_Sens, PCV_EPAP_Sens;
extern int pwm_i_pcv, pwm_e_pcv;
int pwm_max;
float Trs_pcv;


void PCV_Mode()
{
	       
   
	Tt_pcv=6000/PCV_RATE;
	Ti_pcv=(PCV_IT_RATIO*Tt_pcv)/100;
	Te_pcv=Tt_pcv-Ti_pcv;
	
	Trs_pcv=PCV_RISE_TIME*0.2;
	
	if(turbo_speed_high>=0 && turbo_spped_low>=0)
	{
   	if(turbo_speed_high>turbo_spped_low)
	  {
	     trs_step=(int)(turbo_speed_high-turbo_spped_low)/(Trs_pcv);
	  }
  }
	//
		
	
	Tflat_pcv=Ti_pcv-Trs_pcv;
	
	pwm_max=(PCV_MAXP/55.0)*100;
	pwm_i_pcv=(PCV_IPAP/55.0)*100;
	pwm_e_pcv=(PCV_EPAP/55.0)*100;


//============================ determine IPAP	

if(is_inspiratory==1)
{	
			PCV_IPAP_Sens= Current_P1;
          if(Current_P2<=PCV_IPAP)
					{  
     	if((PCV_IPAP_Sens-PCV_IPAP)<=pwm_i_pcv)
			   pwm_i_pcv=pwm_i_pcv-(PCV_IPAP_Sens-PCV_IPAP);
			else
				pwm_i_pcv=pwm_i_pcv;
	
	    turbo_speed_high=pwm_i_pcv;
	    duration_high=Ti_pcv;
	
	
     raise_step=trs_step;
		}
					else
						turbo_speed_high=10;
}


//============================ determine EPAP	

if(is_inspiratory==0)
{	
	
	    PCV_IPAP_Sens= Current_P2;           
     			if(Current_P2>=PCV_EPAP)
					{
	     if((PCV_EPAP_Sens-PCV_EPAP)>pwm_e_pcv)
			  pwm_e_pcv=pwm_e_pcv-(PCV_EPAP_Sens-PCV_EPAP);
       else 
			 pwm_e_pcv= 0;
		  turbo_spped_low=pwm_e_pcv;
	    duration_low=Te_pcv;
	
	     raise_step=trs_step;
		 }
					else
						turbo_spped_low=10;
						
}

//	 delay_unit=(Trs/(pwm_max-pwm_min));	



}
    


