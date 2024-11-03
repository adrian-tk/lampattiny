#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LED_init(void);
void LED_disp(char *arg);
void LED_on(void);
void LED_off(void);
void LED_set(int);
void TCA0_init(void);

void LED_init(void){

	//set pin as a output
    PORTA.DIR |= PIN3_bm;
}

void TCA0_init(void){

	//fclk/(2xTCAprescaler x fds_PWM)
	//3333333/(2x4x1000)~416
	TCA0.SINGLE.PERBUF = 416; 

	//for 50 % duty cycle half of perfbuf
	//for 1 % duty cycle 1/100 of perfbuf
	TCA0.SINGLE.CMP0BUF = 200; 
	
	//PWM mode
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_DSBOTTOM_gc
						|TCA_SINGLE_CMP0EN_bm;

	//disable event counting, default
	//TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	//Set timer with frequency divided 
	//and enable a timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc
						|TCA_SINGLE_ENABLE_bm;
}

void LED_disp(char *arg){
	//for checking if it is a number
	int tmpval = atoi(arg);
	//printf("argument for led: %s\n\r", arg);
	if (strcmp(arg, "") == 0){
		printf("argument needed, try: led help\n\r");
	}
	else if (strcmp(arg, "help") == 0){
		printf("available arguments: help, on, off\n\r");
	}
	else if (strcmp(arg, "on") == 0){
		LED_on();
	}
	else if(strcmp(arg, "off") == 0){
	   	LED_off();
	}

	else if(strcmp(arg, "0") == 0 || (tmpval>0 && tmpval<=100)){
		LED_set(tmpval);
	}

	else{
	   	printf("unknown argument: %s, try: led help\n\r", arg);
	}
}
void LED_on(void){
	printf("turning on led\n\r");
	TCA0.SINGLE.CMP0BUF = TCA0.SINGLE.PERBUF; 
	//PORTA.OUT |= PIN3_bm;
	//TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}
void LED_off(void){
	printf("turning off led\n\r");
	TCA0.SINGLE.CMP0BUF = 0; 
	//TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
	//PORTA.OUT &= ~PIN3_bm;
	//printf("%10x\n\r", PORTA.OUT);
}

void LED_set(int led_perc){
	printf("set led to %d\n\r", led_perc);
	if (led_perc == 0){
		TCA0.SINGLE.CMP0BUF = 0;
	}
	else{
		TCA0.SINGLE.CMP0BUF = TCA0.SINGLE.PERBUF * led_perc / 100;
	}
}
