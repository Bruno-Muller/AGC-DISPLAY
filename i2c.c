/*
 * File:   i2c.c
 * Author: Bruno
 *
 * Created on 6 février 2016, 22:37
 */

#include <xc.h>

#include "display.h"

#define I2C_DISP_ADDRESS    0x10

#define I2C_FRAME_MASK  0x3F

#define I2C_FRAME_START 0
#define I2C_FRAME_END   2

unsigned char buffer[3];

#define channel     buffer[0]
#define data_high   buffer[1]
#define data_low    buffer[2]

void i2c_init() {
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;

    SSPADD = I2C_DISP_ADDRESS << 1;
    //SSPMSK = 0xFF;

    SSPSTATbits.SMP = 0; // Slew rate control enabled for high speed mode (400 kHz)
    //SSPSTATbits.SMP = 1; // Slew Rate Control (limiting) disabled. Operating in I2C Standard mode (100 kHz and 1 MHz).
    SSPSTATbits.CKE = 0; // This bit must be maintained clear. Used in SPI mode only.
    SSPCONbits.CKP = 1; // Release clock stretch

    SSPCONbits.SSPM = 0b0110; // I2C Slave mode, 7-bit address

    SSPCONbits.SSPEN = 1; // Enables the serial port and configures the SDA and SCL pins as serial port pins

    SSPIE = 1;
}

void i2c_interrupt_handler() {
    static unsigned char i = 0;

    unsigned char temp;

    unsigned char digit, left, right, sign;

    temp = SSPBUF; // Read SSPBUF, even for dummy data

    // ADDRESS
    if (SSPSTATbits.D == 0) {
        i = I2C_FRAME_START;
    }        // DATA
    else {
        // READ (slave writes to master)
        if (SSPSTATbits.R == 1) {
        }            // WRITE (slave reads from master)
        else {
            buffer[i] = temp;

            if (i == I2C_FRAME_END) {

                // Is it our channel ?
                if (channel == 0x08) {
                    // ***********************
                    // * Data pattern :      *
                    // * data_high  data_low *
                    // * xAAAABCC   CCCDDDDD *
                    // ***********************

                    // Compute digit pair number
                    digit = (data_high & 0b01111000) >> 3;

                    // compute left digit code
                    temp = (data_low & 0b11100000) >> 5;
                    temp |= (data_high & 0b00000011) << 3;
                    left = digit_code[temp];

                    // compute right digit code
                    temp = (data_low & 0b00011111);
                    right = digit_code[temp];

                    // compute sign
                    temp = (data_high & 0b00000100) >> 2;
                    sign = digit_code[temp];

                    // updates digits
                    display[digit_pair_sign[digit]] = sign;
                    display[digit_pair_left[digit]] = left;
                    display[digit_pair_right[digit]] = right;
                } else if (channel == 0x09) {
                    blinking = (data_low & 0b01000000);
                }
            }
        }
        i++;
    }
}
