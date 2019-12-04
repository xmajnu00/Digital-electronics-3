#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600


int main(void)
{
    TIM_config_prescaler(TIM1, TIM_PRESC_64);       //OBNOVOVACI
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // // Enables interrupts by setting the global interrupt mask
    sei();

    // // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
           
    }

    // Will never reach this
    return (0);
}


 ISR(TIMER1_OVF_vect)
  {

      //uint16_t value = 0;
      //char uart_string[4];
    //   char znak;

  
    //   znak = uart_getc();  

    //   //itoa(value ,uart_string,16);
   
    //  if (znak == '$'){
    //   uart_puts("\n");
    //   uart_puts("\r");
    //   }
     
    //   uart_putc(znak);
  }

