/**
 * @file serial.c
 * @brief Functions for serial output
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

void SCI_Out(long int DATA, unsigned char D, unsigned char N)
{
   unsigned char A[10], i;

   while(!TRMT);
   if(DATA < 0) {
        TXREG = '-';
        DATA = -DATA;
    }
    else TXREG = ' ';
    for (i=0; i<10; i++) {
        A[i] = DATA % 10;
        DATA = DATA / 10;
    }
   for (i=D; i>0; i--) {
        if (i == N) { while(!TRMT); TXREG = '.'; }
        while(!TRMT);  TXREG = A[i-1] + 48;
    }
}

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
