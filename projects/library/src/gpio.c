#include "gpio.h"
/*  Functions  ---------------------------------------------------------*/
void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num)
/*void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num)
void GPIO_config_input_nopull(volatile uint8_t *reg_name , uint8_t pin_num)
void GPIO_config_input_pullup(volatile uint8_t *reg_name,uint8_t pin_num)
void GPIO_write(volatile uint8_t *reg_name,uint8_t pin_num,uint8_t pin_val)
void GPIO_toggle(volatile uint8_t *reg_name,uint8_t pin_num)
uint8_t  GPIO_read(volatile uint8_t *reg_name,uint8_t pin_num)*/

{
    
    // Body of the  function
    *reg_name  |= _BV(pin_num);
    }

 void GPIO_write(volatile uint8_t *reg_name,uint8_t pin_num,uint8_t pin_val) 
 {
    
    
    if (pin_val == 1)
    {
        *reg_name  |= _BV(pin_num);
    }
    else 
    {
            *reg_name  &= _BV(pin_num);
    }
    
    }  
void GPIO_toggle(volatile uint8_t *reg_name,uint8_t pin_num)
{
    
    // Body of the  function
    *reg_name  ^= _BV(pin_num);
    } 