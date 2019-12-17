#include <stdlib.h>         
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>
#include "timer.h"
#include "uart.h"
#include "nokia5110.h"                                                  //display library
#include "gpio.h"
#include "GPS_parsing.h"                                                //gps parsing library (our)


#define UART_BAUD_RATE 9600                                             //defines
#define INT_PIN PD2                                                     //button interrupt
#define GPS_enable PD4                                                  //connect to enable pin of GPS module          


char symbol;        
volatile uint8_t i = 0;
volatile uint8_t end = 0;
volatile uint8_t searching = 1;
volatile uint8_t Continue = 1;                                          //in flowchart named as "pokracuj"

char NMEA[72];
char *NMEA_parse[6];

double lat; double lon; 
char lat_h; char lon_h;
double time;




int main(void)
{

    // EICRA = 0b00000000;   
	//   EIMSK = 0b00000001;

    // DDRD &= ~_BV(INT_PIN);
    // DDRD |= _BV(GPS_enable);
    // PORTD |= _BV(GPS_enable);

    TIM_config_prescaler(TIM1, TIM_PRESC_1024);                         //prescaler- four seconds
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    nokia_lcd_init();                                                   //initializing display

    sei();


    while(1){                                                           //searching for right NMEA sentence
        
         while (!(UCSR0A & (1<<RXC0))){                                 //when data register is not empty

            symbol = uart_getc();

            if (symbol == '$'){                                         // when symbol is dollar, catch sentence

                while(1){
                    
                    while (!(UCSR0A & (1<<RXC0)));
                    NMEA[i] = uart_getc();
                    i++;

                    if(i==70){
                        Continue = 0;
                        break;
                    }             

                }


                NMEA[71] = '\0';
                i = 0;
                
                
                if (strstr(NMEA,"GPGGA") != NULL){                      //if sentence includes "GPGGA" prefix, tokenize the sentence

                    char* token; 
                    char* rest = NMEA;
                    while ((token = strtok_r(rest, ",", &rest))){

                        NMEA_parse[i] = token;
                        i++;
       
                    }

                    lat = atof(NMEA_parse[2]);   
                    lat_h = *NMEA_parse[3];
                    lon = atof(NMEA_parse[4]);   
                    lon_h = *NMEA_parse[5];
                    time = atof(NMEA_parse[1]);


                    end = 1;
                    i = 0;
                    searching = 0;
                    NMEA[0] = '\0';
                    while (Continue != 1);
                    break;

                }

                else{

                    //end = 1;
                    i = 0;
                    NMEA[0] = '\0';
                    searching = 1;
                    while (Continue!= 1);
                    break;
                    
                }

            }    

        }

        //if (end == 1){end = 0; break;}

    }



    // for (;;) {
    // }    
    
    nokia_lcd_write_string("end", 1);                                        //string writing
    nokia_lcd_render();                                                      //string display on Nokia 5110 module
    
    return (0);
}



ISR(TIMER1_OVF_vect)                                                        //graphic output changes every four seconds
{
    nokia_lcd_clear();

    if (searching == 1){
        nokia_lcd_write_string("Lat.:Searching ", 1);   
        nokia_lcd_set_cursor(0, 8);
        nokia_lcd_write_string("Lon.:Searching", 1);
        nokia_lcd_set_cursor(0, 16);
        nokia_lcd_write_string("Time:Searching", 1);

        nokia_lcd_render();
    }

    else {
        nokia_lcd_write_string("Lat.: ", 1);
        latitude_parse_print(lat,lat_h);                                    //using parsing function from NMEA_parse library     
        nokia_lcd_set_cursor(0, 8);
        nokia_lcd_write_string("Lon.: ", 1); 
        longitude_parse_print(lon,lon_h);
        nokia_lcd_set_cursor(0, 16);
        nokia_lcd_write_string("Time: ", 1); 
        time_parse_print(time);
        }

        searching = 1;
        Continue= 1;
        return;
}


// ISR(INT0_vect){                                                          //attempt to make a data sending to computer while disabling GPS

//     TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);    
//     PORTD &= ~_BV(GPS_enable);  
//     uart_puts(NMEA_parse[2]);
//     PORTD |= _BV(GPS_enable); 
//     TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);  

 
// }

