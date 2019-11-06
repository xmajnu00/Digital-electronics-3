/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600


/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX |= _BV(REFS0);  
    ADMUX &= ~_BV(REFS1); 
    ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);  
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);  
    ADCSRA |= _BV(ADIE);  
    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);       //OBNOVOVACI
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Start ADC conversion
    ADCSRA |= _BV(ADSC);  
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
    char uart_string[4];

     //Read 10-bit ACD value
     value = ADC;

    // TODO: Update LCD and UART transmiter
     //lcd_getc();
    //  if(value==0)
    // {
    //  uart_puts("rst");
    // }
    //  if(value=99)
    // {
    //  uart_string='Up';
    // }
     itoa(value ,uart_string , 10);
     //lcd_puts
    lcd_gotoxy(1,1);
    lcd_puts("         ");
    lcd_gotoxy(1,1); 
    lcd_puts(uart_string);

    // uart_puts("\033[4;32m");   // 4:  underline  style; 32:  green  foreground
    // uart_puts("This is all  Green  and  Underlined.");
    // uart_puts("\033[0m");   // 0:  reset  all  attri
    // uart_puts("This is  Normal  text  again.");
   
    uart_puts("\n");
    uart_puts("\r");
    uart_puts(uart_string);
}