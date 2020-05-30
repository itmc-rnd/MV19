#include "check_device_init.h"
#include "stdbool.h"

extern int turbo_speed_high,turbo_spped_low,speed;

bool check_devices()                 /////////////////////// ALARM CHECK
{
	
	 int sum=0;
	   bool pivot =true;
	
	  turbo_speed_high=12,turbo_spped_low=12;
    HAL_Delay(5000);
	   if(speed==0)
		 {
			 pivot=false;		
			 create_response_for_raspberry(111,0);
		 }
		 turbo_speed_high=0,turbo_spped_low=0;
		 
		 for(int cnt=0;cnt<10;cnt++)
		 {
			 sum=sum+pressure(3);
		 }
		 
		 if(sum/10<-1)
		 {
			  pivot=false;		
        create_response_for_raspberry(111,63);   // Pressure Not found
		 }
		 	 
	return true;
}
