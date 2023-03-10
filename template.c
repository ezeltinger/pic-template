/**
 * @file template.c
 * @author Ethan Zeltinger (ezeltinger@gmail.com)
 * @brief A template program for the ECE376 PIC boards
 * 
 */

#include <pic18.h>
#include "lib/lcd_portd.c"
#include "lib/a2d.c"
#include "lib/d2a.c"
#include "lib/keypad.c"
#include "lib/neopixel.c"
#include "lib/serial.c"

const unsigned char MSG0[21] = "Hello World!!       ";

/**
 * @brief This is the main function of your program
 * 
 * @param argc 
 * @param argv 
 * @return int does nothing
 */
int main(int argc, char** argv) {

    //Set PORTA to all outputs
    TRISA = 0;
    TRISB = 0x0F;
    TRISC = 0x0F;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;
    int i;
    LCD_Init();  // initialize the LCD

    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    Wait_ms(500);

    // Initialize the A/D port
    TRISA = 0xFF;
    TRISE = 0x0F;
    ADCON2 = 0x85;
    ADCON1 = 0x07;
    ADCON0 = 0x01;

    while(1) {
        Wait_ms(100);
    }
}

