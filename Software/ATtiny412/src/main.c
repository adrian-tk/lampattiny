//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include "uart/uart.c"
#include "led/led.c"


int main(){
	USART0_init();
	LED_init();

	//turn on interrupt
	sei();

	while (1){
		USART0_flag();
	}
}
