#include "check_device_init.h"
#include "stdbool.h"

extern int turbo_speed_high,turbo_spped_low,speed;
extern bool turbo_error,pressure_s1_error,pressure_s2_error,flow_s_error,buzzer_error;

void check_devices()                 /////////////////////// ALARM CHECK
{
	
	   float sum=0;
	   bool pivot =true;
	
	  turbo_speed_high=12,turbo_spped_low=12;
    HAL_Delay(5000);
	   if(speed==0)
		 {
			 turbo_error=true;		
		 }
		 turbo_speed_high=0,turbo_spped_low=0;
		 
		 for(int cnt=0;cnt<100;cnt++)
		 {
			 sum=sum+pressure(1);
		 }
		 
		 if(sum/100<-1)
		 {
			  pressure_s1_error=true;		
		 }
		 	 
		 for(int cnt=0;cnt<100;cnt++)
		 {
			 sum=sum+pressure(2);
		 }
		 
		 if(sum/100<-1)
		 {
			  pressure_s2_error=true;		
		 }

}

