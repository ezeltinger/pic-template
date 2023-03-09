/**
 * @file serial.c
 * @brief Functions for Serial Communications Interface
 * 
 */

#include <pic18.h>

/**
 * @brief Initialize serial port to 9600 baud
 * 
 */
void serial_init(void)
{
    TRISC = TRISC | 0xC0;
    TXIE = 0;
    RCIE = 0;
    BRGH = 0;
    BRG16 = 1;
    SYNC = 0;
    SPBRG = 255;
    TXSTA = 0x22;
    RCSTA = 0x90;
}

/**
 * @brief Write a string to the serial output
 * Use size so that you don't accidentally write an infinite string
 * 
 * @param str string to write to the serial output
 * @param size number of characters in the string
 */
void SCI_Write(unsigned char *str, unsigned int size)
{
    unsigned int i;

    for (i=0; i<size; i++, str++) {
        while(!TRMT);
        TXREG = *str;
    }
}

/**
 * @brief Send a number to the serial output with a specified number of decimal places
 * 
 * @param data number to write to serial output
 * @param num_digits number of digits in 'data'
 * @param decimal_places number of decimal places in 'data' or where to put the decimal point in 'data'
 */
void SCI_Out(long int data, unsigned char num_digits, unsigned char decimal_places)
{
    unsigned char character_buffer[10], i;

    while(!TRMT);
    if(data < 0) {
        TXREG = '-';
        data = -data;
    }
    else TXREG = ' ';
    for (i=0; i<10; i++) {
        character_buffer[i] = data % 10;
        data = data / 10;
    }
    for (i=num_digits; i>0; i--) {
        if (i == decimal_places) { while(!TRMT); TXREG = '.'; }
        while(!TRMT);  TXREG = character_buffer[i-1] + 48;
    }
}

/**
 * @brief Send carriage return and line feed characters.
 * Equivalent to the new line character \\n.
 * 
 */
void SCI_CRLF(void)
{
    while(!TRMT);  TXREG = 13;
    while(!TRMT);  TXREG = 10;
}

// Example Main Routine
// This program reads the A/D on RA0
// and sends it to the serial port at 9600 baud
// void main(void)
// {
//     int A2D;     // raw A/D readings
//     int VOLT;    // Volts*100 (500 means 5.00V)

//     unsigned int i, j;

//     TRISA = 0;
//     TRISB = 0x0F;
//     TRISC = 0x0F;
//     TRISD = 0;
//     TRISE = 0;
//     ADCON1 = 0x0F;

//     LCD_Init();  // initialize the LCD

//     LCD_Move(0,0);
//     for (i=0; i<20; i++) LCD_Write(MSG0[i]);
//     Wait_ms(500);

//     // Initialize the A/D port
//     TRISA = 0xFF;
//     TRISE = 0x0F;
//     ADCON2 = 0x85;
//     ADCON1 = 0x07;
//     ADCON0 = 0x01;
//     i = 0;

//     // Initialize Serial Port to 9600 baud
//     TRISC = TRISC | 0xC0;
//     TXIE = 0;
//     RCIE = 0;
//     BRGH = 0;
//     BRG16 = 1;
//     SYNC = 0;
//     SPBRG = 255;
//     TXSTA = 0x22;
//     RCSTA = 0x90;

//     while(1) {

//         A2D = A2D_Read(0);

//         VOLT = 0.488*A2D ;

//         LCD_Move(0,10);  LCD_Out(VOLT, 5, 2);

//         SCI_Out(VOLT, 5, 2);
//         SCI_CRLF();

//         Wait_ms(100);

//     }
// }


// Turn on SCI interrupts at 9600 baud
// RISC = TRISC | 0xC0;
// TXIE = 0;
// RCIE = 1;
// BRGH = 1;
// BRG16 = 1;
// SYNC = 0;
// SPBRG = 255;
// TXSTA = 0x22;
// RCSTA = 0x90;

/**
 * @brief An interrupt service routine which
 * Reads in data from the PC
 * Echos back each character as you type it in
 * Saves the message in a buffer, and
 * Looks for a carriage return <13> to terminate the message.
 * 
 */
// void interrupt IntServe(void)
// {
//     if (RCIF) {
//         TEMP = RCREG & 0x7F;
//         TXREG = TEMP;
//         if (TEMP > 20)
//             MSG0[M++] = TEMP;
//         if (M > 21)
//             M = 21;
//         if (TEMP == 13){
//             for (i=M+1; i<21; i++) MSG1[i] = ' ';
//             for (i=0; i<20; i++) {
//                 MSG1[i] = MSG0[i];
//                 MSG0[i] = ' ';
//             } 
//             M = 0;
//         } 
//         RCIF = 0;
//     }
// }

// while(1) {
//     LCD_Move(0,0);
//     for(i=0; i<16; i++) {
//         LCD_Write(MSG1[i]);
//     }
// }
