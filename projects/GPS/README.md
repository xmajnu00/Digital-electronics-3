
# Demo Project

#### Table of Contents

1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Software](#software)
4. [References](#references)

## Introduction
Welcome to our project from course BPC-DE2: GPS module communication.
<br/>
The main task is to create an application with use of Arduino, GPS module and Nokia 5110 display. Our plan was to make Arduino processor catch NMEA sentences data from the GPS module, parse it into substrings latitude, longitude and time and use them in other extensions - displaying the coordinates and time on Nokia display, sending the coordinates and time in simple form into UART, sending them in form of XLM/KML text strings into UART (so they can be saved in computer and used in Google Maps locating, possibly in real time) and in our navigation tool called "Where is Česká".
<br/>
<br/>
Unfortunately, we managed to make only a part of our plan real. Due to problems with developement of algorithms and lack of special equipment we later found necessary we haven't been able to finish everything we wanted.
<br/>
<br/>
With use of VS Studio and C programming language, the main algorithm for data catching, parsing and displaying was made. In infinite loop, we are catching a character using uart_getc function from Peter Fleury's UART library and we are checking it. When a specific symbol $ is found, we check the next 5 characters (prefix of a NMEA sentence). If prefix equals "GPGGA", the right sentence is caught (for this one includes desired data) and so we save the whole sentence into a string. 
<br/>
<br/>
String is then parsed into subtrings by the strtok_r function from <string.h> library and so the data is now ready to be displayed. Every 4 seconds the timer interrupt is used for converting the latitude, longitude and time data into a decimal value and displaying on the Nokia display. For the conversion we use our own library <NMEA_parse.h>, the display is controlled by <nokia5110.h> library made by Sergey Denisov. 
<br/>
<br/>
Our algorithm is not perfect - the GPGGA sentence is not always caught and desired data is not always available for displaying. In case the timer interrupt activates and the data is not available, string "searching" is displayed instead of the substrings with old data. Also, our application suffers from an error, which is causing occasional invalid data displaying. This can be observed from the video. We believe its caused by the speed of data parsing (currently parsed data possibly can be overwrote by the data from next main loop iteration). We tried to solve this by short time UART disabling, unfortunately this did not work. 
<br/>
<br/>
Most of the commercial GPS modules provide an enable pin. We wanted to make use of this in our "data sending to computer" task. Output pin PD4 - GPS enable was intended to be connected with a possible enable pin of a GPS module, its logical level was to be controlled by a button connected to INT0 interrupt pin. By pressing this button we wanted the enable pin to be pulled down to low level, so the GPS would become inactive and the UART bus cleared. After this, the saved latitude, longitude and time data strings could be uploaded to UART data bus (with no risk of UART errors - our Arduino board have only one UART input/output and the case of more devices connected to it at the same time commonly cause errors). Also this part of our code does not seem to work, possibly because of wrong circuitry/mistakes in interrupt code.
<br/>
<br/>
Unfortunately, our attempts of solving the mentioned imperfections no time was left for developement of our extensions.
<br/>
<br/>
One of our ideas was to develop a XML/KML pseudo-generator, which would be uploading specific strings into UART, including our latitude and longitude data. These strings could then be catched by a computer, saved into a text document as an XML and used as geolocation data in Google Maps software, which is compatible with KML format. The example of content of a KML file is shown below:
<br/>
<br/>

![XML/KML](https://github.com/xmaluc00/Digital-electronics-2/blob/master/projects/GPS/kml.PNG)

<br/>
<br/>
-- source: https://developers.google.com/kml/documentation/kml_tut
<br/>
<br/>
The second of our ideas was to develop a navigation tool called "Where is Česká", a simple compass pointing towards Česká tram stop instead of North. This could be done by implementation of a standard compass using Arduino HMC5883L module - a magnetometer measuring Earth's magnetic lines of force, outputting a direction in angles between our heading and magnetic north. The direction could be displayed on the Nokia display with simple graphics and updated several times a second. To display Česká direction instead of the magnetic North, we could compute a value of an angle between relatively static magnetic North, our dynamic position and static Česká position and subtract it from the North angle with every update. 




## Hardware
GPS module PA6H (Drotek Electronics) <br/>  Display Nokia 5110 <br/> Microcontroller Arduino UNO (ATmega328P) <br/>

## Software
Microsoft Visual Studio <br/>
Fritzinh 

## References
1. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)

2. Our GitHub repository: https://github.com/xmaluc00/Digital-electronics-2

3. Other sources: <br/>  https://github.com/LittleBuster/avr-nokia5110 <br/> https://navody.arduino-shop.cz/navody-k-produktum/lcd-displej-nokia-5110.html <br/> http://yopero-tech.blogspot.com/ <br/> http://www.tajned.cz/ 
4. Video link: https://www.youtube.com/watch?v=jfIPIAEUn_A&feature=youtu.be
