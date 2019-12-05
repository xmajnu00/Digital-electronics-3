// #include <stdlib.h>             // itoa() function
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include "timer.h"
// #include "lcd.h"
// #include "uart.h"
// #include "nokia5110.h"
// #include "nokia5110_chars.h"
// #include "twi.h"

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

//volatile uint16_t i = 0;
char prefix[15];
char pre_prefix[15];
char znak;

int main(void)
{

   uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // TIM_config_prescaler(TIM1, TIM_PRESC_64);strstr(uart_string,"$GPGGA,") == NULL
    // TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

   sei();

    while (1){

        znak = uart_getc();

        if (znak == '$'){

          for (int i = 0; i<7; i++){

              znak = uart_getc();
              *(pre_prefix+i) = znak;

              strncpy(prefix, pre_prefix, 15);
              prefix[15] = '\0';

              nokia_lcd_init();
              nokia_lcd_clear();
              nokia_lcd_write_string(prefix, 1); 
              nokia_lcd_render();

          }

        if (strstr(prefix,"GPGGA,") != NULL){

          nokia_lcd_init();
          nokia_lcd_clear();
          nokia_lcd_write_string("nalezeno", 1); 
          nokia_lcd_render();
          //break;


        }


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