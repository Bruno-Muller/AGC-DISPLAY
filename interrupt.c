/*
 * File:   interrupt.c
 * Author: Bruno
 *
 * Created on 6 février 2016, 23:17
 */

#include <xc.h>

#include "i2c.h"

void interrupt interrupt_handler() {
    if (SSPIF) {
        SSPIF = 0; // Clear interrupt flag
        i2c_interrupt_handler();
    }
}