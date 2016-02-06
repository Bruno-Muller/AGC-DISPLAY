/* 
 * File:   display.h
 * Author: Bruno
 *
 * Created on 6 février 2016, 23:16
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

// Translation tables for 7seg addressing through decoders
extern const unsigned char decoder_i[];
extern const unsigned char decoder_j[];

// Contains the 7 segments codes to display
extern unsigned char display[];

// Translation table from "AGC digit code" to "7 segments code"
extern const unsigned char digit_code[];
extern const unsigned char digit_pair_left[];
extern const unsigned char digit_pair_right[];
extern const unsigned char digit_pair_sign[];

extern unsigned char blinking;

#endif	/* DISPLAY_H */

