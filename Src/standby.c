#include "standby.h"
#include "driver.h"

void start_standby()
{
			   int start_command=rspy_receive_buffer[3];
	       if(start_command==0)
					{
  				 /*char buf[50];
	  			 sprintf(buf, "\r\n START Standby....\r\n");
		  		 print_debug((uint8_t *)buf, strlen(buf));*/
					turbo(20);
					}
					else
					{
						 /*char buf[50];					
					   sprintf(buf, "%s","\r\n STANDBY DATA Error!!!!\r\n");						
					   print_debug((uint8_t *)buf, 18);*/
					}
					

}
