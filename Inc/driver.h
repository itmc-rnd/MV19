#ifndef __DRIVER_H
#define __DRIVER_H



void ADC_CNL(int x);
int ADC_READ(int x);
void delay(int x);
void led(int x,int y);
int bcd2bin(int bcd);
void turbo(int x);
void buzzer(int x,int y);
void flash(int x,int y);
int sec(void);
int min(void);
int hour(void);
int day(void);
int month(void);
int year(void);
void driver_init(void);
void turbo_break(int x);
float pressure(int x);
float flow(int x);


#endif

