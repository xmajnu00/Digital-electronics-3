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
#define 	UCSRA 	UCSR0A
#define 	RXC 	RXC0
#define 	UDR 	UDR0
#define   UART_BAUD_RATE 9600

volatile uint16_t i = 0;
char uart_string[200];
char znak;
char test_prefix[] = "abcde";


int main(void)
{

   uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

   sei();
  

   while(1){

      while (!(UCSRA & (1<<RXC)));
      *(uart_string+i) = UDR;
      i++;
      if (strstr(uart_string,"$GPGGA,") != NULL){

        uart_string[199] = '\0';
        nokia_lcd_init();
        nokia_lcd_clear();
        nokia_lcd_write_string(uart_string, 1); 
        nokia_lcd_render();       
        return 0;   
        
      }
    }




    return (0);
}










// ISR(TIMER1_OVF_vect)
// {

//   char znak;
//   znak = uart_getc();
//   lcd_string[i] = znak;
//   i++;
  


//   nokia_lcd_init();
//   nokia_lcd_clear();
//   nokia_lcd_write_string(lcd_string, 1); 
//   nokia_lcd_render();

   

//   //itoa(value ,uart_string,16);

//   //if (znak == '$'){
//   //   uart_puts("\n");
//   //   uart_puts("\r");
//   // }
     
//   //uart_putc(znak);

// }