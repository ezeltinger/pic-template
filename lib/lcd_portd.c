/**
 * @file lcd_portd.c
 * @brief LCD helper functions
 * 
 */

#include <pic18.h>

void Wait_ms(unsigned int X);
void LCD_Pause(void);
void LCD_Strobe(void);
void LCD_Inst(unsigned char c);
void LCD_Move(unsigned char Row, unsigned char Col);
void LCD_Write(unsigned char c);
void LCD_Init(void);
void LCD_Out(long int DATA, unsigned char D, unsigned char N);

/**
 * @brief Wait for ms milliseconds
 * Note that 617 noops plus a for loop approximately equals 1ms
 * 
 * @param ms time to wait in milliseconds
 */
void Wait_ms(unsigned int ms)
{
    unsigned int i, j;

    for (i=0; i<ms; i++)
        for (j=0; j<617; j++);
}

/**
 * @brief A simple pause for the LCD so that
 * operations aren't executed to quickly.
 * 
 */
void LCD_Pause(void)
{
    unsigned char x;
    for (x=0; x<20; x++);
}

/**
 * @brief Refresh LCD screen
 * 
 */
void LCD_Strobe(void)
{
    RD3 = 0;
    LCD_Pause();
    RD3 = 1;
    LCD_Pause();
    RD3 = 0;
    LCD_Pause();
}

/**
 * @brief Write an instruction to the LCD controller in 4 bit mode
 * 
 * @param c Instruction byte to write to the LCD
 * @return void
 */
void LCD_Inst(unsigned char c)
{
    RD2 = 0; // send an instruction
    PORTD = (PORTD & 0x0F) |  (c & 0xF0);
    LCD_Strobe();
    PORTD = (PORTD & 0x0F) |  ((c<<4) & 0xF0);
    LCD_Strobe();
    Wait_ms(10);
}

/**
 * @brief Move the LCD cursor to a position on the LCD
 * 
 * @param Row On ECE376 PIC boards can only be 0 or 1
 * @param Col Column on the LCD from 0 to 19
 */
void LCD_Move(unsigned char Row, unsigned char Col)
{
    if (Row == 0) LCD_Inst(0x80 + Col);
    if (Row == 1) LCD_Inst(0xC0 + Col);
    if (Row == 2) LCD_Inst(0x94 + Col);
    if (Row == 3) LCD_Inst(0xD4 + Col);
}

/**
 * @brief Write an ASCII character to the LCD
 * 
 * @param c character to write
 */
void LCD_Write(unsigned char c)
{
    RD2 = 1; // send data
    PORTD = (PORTD & 0x0F) | (c & 0xF0);
    LCD_Strobe();
    PORTD = (PORTD & 0x0F) | ((c<<4)  & 0xF0);
    LCD_Strobe();

}

/**
 * @brief Initialize the LCD
 * 
 */
void LCD_Init(void)
{
    TRISD = 0x01;
    RD1 = 0;
    LCD_Inst(0x33);
    LCD_Inst(0x32);
    LCD_Inst(0x28);
    LCD_Inst(0x0E);
    LCD_Inst(0x01);
    LCD_Inst(0x06);
    Wait_ms(100);
}

/**
 * @brief Write a number to the LCD with a specified number of decimal places
 * 
 * @param data number to write to serial output
 * @param num_digits number of digits in 'data'
 * @param decimal_places number of decimal places in 'data' or where to put the decimal point in 'data'
 */
void LCD_Out(long int data, unsigned char num_digits, unsigned char decimal_places)
{
    unsigned char character_buffer[10], i;

    if(data < 0) {
        LCD_Write('-');
        data = -data;
    }
    else LCD_Write(' ');
    for (i=0; i<10; i++) {
        character_buffer[i] = data % 10;
        data = data / 10;
    }
    for (i=num_digits; i>0; i--) {
        if (i == decimal_places) LCD_Write('.');
        LCD_Write(character_buffer[i-1] + '0');
    }
}
