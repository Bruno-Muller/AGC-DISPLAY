/*
 * File:   io.c
 * Author: Bruno
 *
 * Created on 6 février 2016, 22:37
 */

#include <xc.h>

// input/output configuration register
#define DEFAULT_PORTA   0b00001000
#define DEFAULT_ANSELA  0x00
#define DEFAULT_TRISA   0b11110000

#define DEFAULT_PORTB   0b00000000
#define DEFAULT_ANSELB  0x00
#define DEFAULT_TRISB   0b00000000

#define DEFAULT_PORTC   0b00000000
#define DEFAULT_TRISC   0b11111100

void io_init() {
    // Init ports
    PORTA = DEFAULT_PORTA;
    ANSELA = DEFAULT_ANSELA;
    TRISA = DEFAULT_TRISA;

    PORTB = DEFAULT_PORTB;
    ANSELB = DEFAULT_ANSELB;
    TRISB = DEFAULT_TRISB;

    PORTC = DEFAULT_PORTC;
    TRISC = DEFAULT_TRISC;
}
