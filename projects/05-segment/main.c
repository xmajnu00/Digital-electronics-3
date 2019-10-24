/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

volatile uint16_t i = 0;

volatile uint8_t jednotky = 0;
volatile uint8_t desitky = 0;
volatile uint8_t stovky = 0;
volatile uint8_t tisice = 0;

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */

int main(void)
{
    /* D1 led */

    

    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write(&PORTB,LED_D1, 1);

    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9

    PCICR = PCICR | _BV(PCIE1);
    PCMSK1 |=  _BV(PCINT11) | _BV(PCINT10) | _BV(PCINT9);

    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    TIM_config_prescaler(TIM1, TIM_PRESC_1);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    TIM_config_prescaler(TIM0, TIM_PRESC_1);                //OBNOVOVACI
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
   
    GPIO_config_output(&DDRB , SEGMENT_DATA );
    GPIO_config_output(&DDRD , SEGMENT_CLK );
    GPIO_config_output(&DDRD , SEGMENT_LATCH );

    /* Enable interrupts by setting the global interrupt mask */
    sei();

    /* Infinite loop */

    for (;;) {

        // TODO: Use function to display digit 1 at position 0
        //SEG_putc(0, 1);
    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */
ISR(PCINT1_vect)
{
    GPIO_toggle(&PORTB, LED_D1);
    // TODO: Toggle a led

}
ISR(TIMER0_OVF_vect)
{
    SEG_putc(jednotky, 0);
    SEG_putc(desitky, 1);
    SEG_putc(stovky, 2);
    SEG_putc(tisice, 3);
    
}


ISR(TIMER1_OVF_vect)
{
    
    /*SEG_putc(i, 0);               //jeden digit od 0 do 9
    i++;
    if (i > 9) 
    {
        i = 0;
    }*/
    
    jednotky = i%10;
    desitky = (i/10) %10;
    stovky = (i/100) %10;
    tisice = i/1000;

    i++;

    if (i > 9999) 
    {
        i = 0;
    }

}

