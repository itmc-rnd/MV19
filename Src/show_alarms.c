#include "show_alarms.h"



 AlarmData show_alarm(int alarm_id)
{
	  
	  int Fault_alarm=0;
	  int ac_power=0;
	
	   AlarmData alarm={0,"","",false,false};
	
	if(alarm_id==1)
  {
	   
		if( Fault_alarm==1)
		{
			   alarm.id=1;
		     alarm.message="AC POWER DISCONNECTION";
		     alarm.messageType="MP";
		     alarm.Audio_Paused_available=true;
		     alarm.Alarm_Paused_available=true;
		}
			else
			{
				 alarm.id=1;
		     alarm.message="AC POWER DISCONNECTION";
		     alarm.messageType="LP";
		     alarm.Audio_Paused_available=true;
		     alarm.Alarm_Paused_available=true;
		}

		  
  }
	else if (alarm_id==2)
	{

	//messageType="MP"; //expect for cpap
				alarm.id=2;
				alarm.message="APNEA";
				alarm.messageType="MP";
				alarm.Audio_Paused_available=true;
				alarm.Alarm_Paused_available=true;
	}	
		else if (alarm_id==3)
			{
				alarm.id=3;
				alarm.message="BATTERY FAULT1 RESTART/SRVC";
				alarm.messageType="MP";
				alarm.Audio_Paused_available=true;
				alarm.Alarm_Paused_available=true;
								
			}
				
				else if (alarm_id==4)
				{
						alarm.id=4;
						alarm.message="BATTERY FAULT2 RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;
															
				}

				else if (alarm_id==5)
				{
						alarm.id=5;
						alarm.message="BUZZER FAULT1 RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;
					
				}
					
				else if (alarm_id==6)
				{
						alarm.id=6;
						alarm.message="BUZZER FAULT2 RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;
			
				}
				
				else if (alarm_id==7)
				{
					
						alarm.id=7;
						alarm.message="BUZZER FAULT3 RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;
					
				}
				
			else if (alarm_id==8)
				{
					 

						alarm.id=8;
						alarm.message="BUZZER LOW BATTERY";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;

				}
				
		else if (alarm_id==9)
				{
						alarm.id=9;
						alarm.message="CALIBRATE FiO2";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;
					
				}
				else if (alarm_id==10)
				{
						alarm.id=10;
						alarm.message="CALIBRATION FAIL";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;					 
			
				}
				
				else if (alarm_id==11)
				{
					
						alarm.id=11;
						alarm.message="CHECK BATTERY CHARGE IF PERSISTS RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;					 
	
				}
				
       else if (alarm_id==12)
				{
					  alarm.id=12;
						alarm.message="CHECK EXH VALVE**IF PERSISTS RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;			
					
				}
			else if (alarm_id==13)
				{
						alarm.id=13;
						alarm.message="CHECK EXH VALVE PRESSURE";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								

				}
				else if (alarm_id==14)
				{
						alarm.id=14;
						alarm.message="CHECK FiO2 SENSOR";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==15)
				{
						alarm.id=15;
						alarm.message="CHECK PROXIMAL LINE1**IF PERSISTS RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
						
				}
							
			else if (alarm_id==16)
				{
						alarm.id=16;
						alarm.message="CHECK REMOTE ALARM";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
				}
					else if (alarm_id==17)
				{
						alarm.id=17;
						alarm.message="CHECK SETTINGS";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
								
				}
				else if (alarm_id==18)
				{
						alarm.id=18;
						alarm.message="CONNECT VALVE OR CHANGE PRESS";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								

				}
				
				else if (alarm_id==19)
				{
														

					 //alarm={19,"CONTROLLED CYCLES","N/A","N/A","N/A"};
					
				}
					else if (alarm_id==20)
				{
						alarm.id=20;
						alarm.message="COOLING FAN RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
					
				}
				else if (alarm_id==21)
				{
						alarm.id=21;
						alarm.message="DC POWER DISCONNECTION";
						alarm.messageType="LP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
					
				}
				else if (alarm_id==22)
				{
						alarm.id=22;
						alarm.message="DEVICE FAULT3 RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==23)
				{
						alarm.id=23;
						alarm.message="DEVICE FAULT5 RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								

				}
				
				else if (alarm_id==24)
				{
						alarm.id=24;
						alarm.message="DEVICE FAULT7 RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
	
				}
				
				else if (alarm_id==25)
				{
						alarm.id=25;
						alarm.message="DEVICE FAULT9 RESTART/SRVC";
						alarm.messageType="VHP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;								
				
				}
				else if (alarm_id==26)
				{
						alarm.id=26;
						alarm.message="DEVICE FAULT10 RESTART/SRVC";
						alarm.messageType="VHP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;								
			
				}
			else if (alarm_id==27)
				{
						alarm.id=27;
						alarm.message="DEVICE FAULT11 RESTART/SRVC";
						alarm.messageType="VHP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;								

				}
					else if (alarm_id==28)
				{
						alarm.id=28;
						alarm.message="DEVICE FAULT12 RESTART/SRVC";
						alarm.messageType="VHP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==29)
				{
						alarm.id=29;
						alarm.message="DEVICE FAULT13 RESTART/SRVC";
						alarm.messageType="VHP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;								
					
					
				}	
   else if (alarm_id==30)
				{
					alarm.id=30;
					alarm.message="E SENS FAULT OR CIRC LEAK";
					alarm.messageType="MP";
					alarm.Audio_Paused_available=true;
					alarm.Alarm_Paused_available=false;								
					
				}
   else if (alarm_id==31)
				{
				
					if ( ac_power==0)
					{
						alarm.id=31;
						alarm.message="EMPTY BATTERY";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								

					}
						else
						{
						alarm.id=31;
						alarm.message="EMPTY BATTERY";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
					}
				
				}				

				 else if (alarm_id==32)
				{
						alarm.id=32;
						alarm.message="EXH VALVE LEAKAGE";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
						}
				else if (alarm_id==33)
				{
						alarm.id=33;
						alarm.message="FiO2 SENSOR MISSING";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
					
				}
				else if (alarm_id==34)
				{
						alarm.id=34;
						alarm.message="HIGH / LOW BATTERY TEMP**IF PERSISTS RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
					
				}
				else if (alarm_id==35)
				{
						alarm.id=35;
						alarm.message="HIGH FiO2";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==36)
				{
						alarm.id=36;
						alarm.message="HIGH INT TEMP COOL VENT**IF PERSISTS RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;								
					
				}
				else if (alarm_id==37)
				{
						alarm.id=37;
						alarm.message="HIGH LEAKAGE";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==38)
				{
						alarm.id=38;
						alarm.message="HIGH PRESSURE";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==39)
				{
						alarm.id=39;
						alarm.message="HIGH RATE";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
					
				else if (alarm_id==40)
				{
						alarm.id=40;
						alarm.message="HIGH VTE";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==41)
				{
						alarm.id=41;
						alarm.message="HIGH VTI";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;								
					
				}
				else if (alarm_id==42)
				{
						alarm.id=42;
						alarm.message="INSP FLOW RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		

				}
				else if (alarm_id==43)
				{
						alarm.id=43;
						alarm.message="INTENTIONAL VENT STOP";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;		
				
				}
				else if (alarm_id==44)
				{
						alarm.id=44;
						alarm.message="KEYPAD FAULT RESTART/SRVC* *IF PERSISTS RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==45)
				{
					
					
					if(ac_power==0)
					{						
						alarm.id=45;
						alarm.message="LOW BATTERY";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
					}
					else
					{
						alarm.id=45;
						alarm.message="LOW BATTERY";
						alarm.messageType="LP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		

					}
				}
				
				
				else if (alarm_id==46)
				{
						alarm.id=46;
						alarm.message="LOW FiO2";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==47)
				{
						alarm.id=47;
						alarm.message="LOW VTE";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==48)
				{
						alarm.id=48;
						alarm.message="LOW VTI";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
				}
				else if (alarm_id==49)
				{
						alarm.id=49;
						alarm.message="OCCLUSION CHECK CIRCUIT**IF PERSISTS RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
				}
				else if (alarm_id==50)
				{
						alarm.id=50;
						alarm.message="OCCLUSION CHECK CIRCUIT";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
				
				}
				else if (alarm_id==51)
				{
						alarm.id=51;
						alarm.message="PATIENT DISCONNECTION**IF PERSISTS RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
				
				}
				else if (alarm_id==52)
				{
						alarm.id=52;
						alarm.message="POWER FAULT RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;		
					
				}
				else if (alarm_id==53)
				{
						alarm.id=53;
						alarm.message="POWER SUPPLY LOSS";
						alarm.messageType="VHP";
						//alarm.Audio_Paused_available=true;
						//alarm.Alarm_Paused_available=true;		

					
	//	Audio_Paused_available="NO ALARM"; //Cancle only
	//	Alarm_Paused_available="NO ALARM"; //cancel only
				}
				else if (alarm_id==54)
				{
						alarm.id=54;
						alarm.message="PRES SENS FLT1 RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==55)
				{
						alarm.id=55;
						alarm.message="PROX SENS FLT2 RESTART/SRVC";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=true;		
					
				}
				else if (alarm_id==56)
				{
						alarm.id=56;
						alarm.message="REMOVE VALVE CPAP MODE";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		

				}
				else if (alarm_id==57)
				{
						alarm.id=57;
						alarm.message="REMOVE VALVE OR CHANGE PRES";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==58)
				{
						//alarm.id=58;
						//alarm.message="SOFTWARE VERSION ERROR";
						//alarm.messageType="HP";
						//alarm.Audio_Paused_available=true;
						//alarm.Alarm_Paused_available=true;		
					
 //alarm={58,,"N/A","N/A","N/A"};
				//	Audio_Paused_available="N/A";
		//Alarm_Paused_available="N/A";
								}
				else if (alarm_id==59)
				{
						alarm.id=59;
						alarm.message="TURB OVERHEAT RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=false;
						alarm.Alarm_Paused_available=false;		
				}
				else if (alarm_id==60)
				{
						alarm.id=60;
						alarm.message="UNKNOWN BATTERY";
						alarm.messageType="MP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==61)
				{
						alarm.id=61;
						alarm.message="VALVE MISSING CONNECT VALVE";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;		
					
				}
				else if (alarm_id==62)
				{
							alarm.id=62;
						alarm.message="VTI NOT REACHED**IF PERSISTS RESTART/SRVC";
						alarm.messageType="HP";
						alarm.Audio_Paused_available=true;
						alarm.Alarm_Paused_available=false;			
				}
        return alarm;
			}
