/* 
 * File:   io.h
 * Author: Bruno
 *
 * Created on 6 février 2016, 22:37
 */

#ifndef IO_H
#define	IO_H

// Decoder
#define DECODER_SELECT  RA3 // output
#define DECODER_C1      RA0 // output
#define DECODER_C2      RA1 // output
#define DECODER_C3      RA2 // output
#define DECODER_R1      RC0 // output
#define DECODER_R2      RC1 // output

#define BLINK_SYNC      RA4 // output

#define decoder_assert()      DECODER_SELECT = 0
#define decoder_disassert()   DECODER_SELECT = 1

void io_init();

#endif	/* IO_H */

