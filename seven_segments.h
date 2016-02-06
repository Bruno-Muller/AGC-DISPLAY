/* 
 * File:   seven_segments.h
 * Author: Bruno
 *
 * Created on 6 février 2016, 23:24
 */

#ifndef SEVEN_SEGMENTS_H
#define	SEVEN_SEGMENTS_H

/********************
 * 7 segments codes *
 ********************/
#define ZERO    0x3F
#define ONE     0x06
#define TWO     0x5B
#define THREE   0x4F
#define FOUR    0x66
#define FIVE    0x6D
#define SIX     0x7D
#define SEVEN   0x07
#define EIGHT   0x7F
#define NINE    0x6F
#define MINUS   0x40
#define BLANK   0x00
#define POINT   0x80
#define ERROR   0b01100001  // used for debugging purpose

// Translatation table from "a number" to "7 segments code"
extern const unsigned char seg[];

#endif	/* SEVEN_SEGMENTS_H */

