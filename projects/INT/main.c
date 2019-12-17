#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include "nokia5110.h"
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600
#define INT_PIN PD3
#define GPS_enable PD4


int main(void)
{

  sei();

  EICRA = 0b00000001;   
	EIMSK = 0b00000001;

  DDRD &= ~_BV(INT_PIN);
  DDRD |= _BV(GPS_enable);
  PORTD |= _BV(GPS_enable);


  for(;;){
  };
    
    
  return (0);
}




ISR(INT0_vect){

  PORTD ^= _BV(GPS_enable);
 
}