/**
 * @file d2a.c
 * @brief D2A output helper functions
 * 
 */

#include <pic18.h>

void D2A(unsigned int X)
{
    unsigned char i;
    TRISC0 = 0;
    TRISC3 = 0;
    TRISC5 = 0;

    // Add 0011 to the first four bits to set up the D/A
    X = X & 0x0FFF;
    X = X + 0x3000;
    RC0 = 1;
    RC3 = 1;

    // CS goes low to select the D/A chip
    RC0 = 0;

    // Send out 16 bits of data
    for (i=0; i<16; i++) {
        if (X & 0x8000) RC5 = 1; else RC5 = 0;
        RC3 = 0;
        X = X << 1;
        RC3 = 1;
    }

    // CS goes high to terminate the communicaitons
    RC0 = 1;
}

// Square Wave
void d2a_square(void)
{
    unsigned int i;
    while(1) {
        D2A(1638);
        for(i=1; i<3100; i++);
        D2A(2457);
        for(i=0; i<3100; i++);
    }
}

// Sawtooth Wave
void d2a_sawtooth(void)
{
   unsigned int x, i;
   x = 1638;
   while(1) {
        D2A(x);
        x = x + 10;
        if(x > 2457) x = 1638;
        for(i=0; i<100; i++);
    }
}

// Triangle Wave
void d2a_triangle(void)
{
    unsigned int x, dx, i;
    x = 1638;
    dx = +10;
    while(1) {
        D2A(x);
        x = x + dx;
        if(x > 2457) dx = -10;
        if(x < 1638) dx = +10;
        for(i=0; i<100; i++);
    }
}

//Parabolic Sine Wave
void d2a_sin(void)
{
    unsigned int x, dx, y, i;
    x = 0;
    dx = 0;
    while(1) {
        x = (x + 1) % 64;
        if(x == 0) dx = dx ^ 1;
        if(dx) y = 2048 + (2 * x * (64-x))/5;
        else y = 2048 - (2 * x * (64-x))/5;
        D2A(y);
        for(i=0; i<100; i++);
    }
}
