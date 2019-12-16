
# Demo Project

#### Table of Contents

1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Software](#software)
4. [References](#references)

## Introduction
Welcome to our project from course BPC-DE2: GPS module communication.
<br/>
The main task is to create an application with use of Arduino, GPS module and Nokia 5110 display. Our plan was to make Arduino processor catch NMEA sentences data from the GPS module, parse it into substrings latitude, longitude and time and use them in other extensions - displaying the coordinates and time on Nokia display, sending the coordinates and time in simple form into UART, sending them in form of XLM/KML text strings into UART (so they can be saved in computer and used in Google Maps locating, possibly in real time) and in our navigation tool called "Where is Česká" for computing 

## Hardware
GPS module PA6H (Drotek Electronics) <br/>  Display Nokia 5110 <br/> Microcontroller Arduino UNO (ATmega328P) <br/>

## Software
Microsoft Visual Studio <br/>
Fritzing

## References
1. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)

2. Our GitHub repository: https://github.com/xmaluc00/Digital-electronics-2

3. Other sources: <br/>  https://github.com/LittleBuster/avr-nokia5110 <br/> https://navody.arduino-shop.cz/navody-k-produktum/lcd-displej-nokia-5110.html <br/> http://yopero-tech.blogspot.com/ <br/> http://www.tajned.cz/ 
4. Video link: https://www.youtube.com/watch?v=jfIPIAEUn_A&feature=youtu.be
