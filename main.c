/* 
 * File:   main.c
 * Author: Bruno
 *
 * Created on 14 novembre 2015, 19:08
 */

#include <xc.h>

#include "conf.h"
#include "display.h"
#include "i2c.h"
#include "io.h"
#include "seven_segments.h"

void init() {
    /*  Oscillator :
     *  16 MHz
     */
    OSCCON = 0x30;

    /* Option :
     * PORTB pull-ups are disabled
     * Interrupt on falling edge of INT pin
     * Internal instruction cycle clock (FOSC/4)
     * Increment on low-to-high transition on T0CKI pin
     * Prescaler is assigned to the Timer0 module
     * Prescaler Rate Select bits Timer0 1:2
     */
    OPTION_REG = 0x80;

    io_init();
    i2c_init();

    PEIE = 1;
    ei();
}

void main(void) {

    init();

    unsigned char index, i, j, segments;

    while (1) {

        for (index=0;index<24;index++) {
            
            // Compute i & j decoders address
            i = (PORTA & ~0x07) | (decoder_i[index] & 0x07);
            j = (PORTC & ~0x03) | (decoder_j[index] & 0x03);
            
            // Get segment code
            segments = display[index];

            // If segments are blinking
            if ((blinking != 0) && (BLINK_SYNC == 0) && (index >= 2) && (index <= 5)) segments = BLANK;

            // For debugging purpose
            if ((index == 20) && (SSPIF == 1)) segments = POINT;
            else if ((index == 21) && (SSPSTATbits.BF == 1)) segments = POINT;
            else if ((index == 22) && (SSPCONbits.WCOL == 1)) segments = POINT;
            else if ((index == 23) && (SSPCONbits.SSPOV == 1)) segments = POINT;
            
            // Turn off segments
            decoder_disassert();
            PORTB = 0;
            
            // Set decoder address
            PORTA = i;
            PORTC = j;

            // Update segments
            PORTB = segments;

            // Turn on segments
            decoder_assert();

            __delay_us(400);
        }
    }
}

