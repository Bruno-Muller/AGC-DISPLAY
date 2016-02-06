/*
 * File:   display.c
 * Author: Bruno
 *
 * Created on 6 février 2016, 23:16
 */

#include "display.h"

#include "seven_segments.h"


// Translation tables for 7seg addressing through decoders
const unsigned char decoder_i[] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5};
const unsigned char decoder_j[] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

// Contains the 7 segments codes to display (can init the array here if needed)
unsigned char display[] = {
    BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
    BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
    BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,
    0 // the last one (this one) is a trash digit (not displayed) used for unexpected or unhandled writes
};

/********************
 * AGC digits codes *
 ********************/
#define DIGIT_BLANK     0b00000000
#define DIGIT_ZERO      0b00010101
#define DIGIT_ONE       0b00000011
#define DIGIT_TWO       0b00011001
#define DIGIT_THREE     0b00011011
#define DIGIT_FOUR      0b00001111
#define DIGIT_FIVE      0b00011110
#define DIGIT_SIX       0b00011100
#define DIGIT_SEVEN     0b00010011
#define DIGIT_EIGHT     0b00011101
#define DIGIT_NINE      0b00011111
#define DIGIT_MINUS     0b00000001 // not AGC's, but used here to trick the algorithm

// Translation table from "AGC digit code" to "7 segments code"
const unsigned char digit_code[] = {
    BLANK,MINUS,ERROR,ONE,ERROR,ERROR,ERROR,ERROR,
    ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,FOUR,
    ERROR,ERROR,ERROR,SEVEN,ERROR,ZERO,ERROR,ERROR,
    ERROR,TWO,ERROR,THREE,SIX,EIGHT,FIVE,NINE
};

#define DIGIT_M1M2      0b00001011
#define DIGIT_V1V2      0b00001010
#define DIGIT_N1N2      0b00001001
#define DIGIT_11        0b00001000
#define DIGIT_1213      0b00000111
#define DIGIT_1415      0b00000110
#define DIGIT_2122      0b00000101
#define DIGIT_2324      0b00000100
#define DIGIT_2531      0b00000011
#define DIGIT_3233      0b00000010
#define DIGIT_3435      0b00000001
#define DIGIT_RESERVED  0b00001100

#define DIGIT_TRASH     24

#define DIGIT_M1M2_L    0
#define DIGIT_V1V2_L    2
#define DIGIT_N1N2_L    4
#define DIGIT_1213_L    8
#define DIGIT_1415_L    10
#define DIGIT_2122_L    13
#define DIGIT_2324_L    15
#define DIGIT_2531_L    17
#define DIGIT_3233_L    20
#define DIGIT_3435_L    22
const unsigned char digit_pair_left[] = {
    DIGIT_TRASH,DIGIT_3435_L,DIGIT_3233_L,DIGIT_2531_L,
    DIGIT_2324_L,DIGIT_2122_L,DIGIT_1415_L,DIGIT_1213_L,
    DIGIT_TRASH,DIGIT_N1N2_L,DIGIT_V1V2_L,DIGIT_M1M2_L,
    DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH
};

#define DIGIT_M1M2_R    1
#define DIGIT_V1V2_R    3
#define DIGIT_N1N2_R    5
#define DIGIT_1213_R    9
#define DIGIT_11_R      7
#define DIGIT_1415_R    11
#define DIGIT_2122_R    14
#define DIGIT_2324_R    16
#define DIGIT_2531_R    19
#define DIGIT_3233_R    21
#define DIGIT_3435_R    23
const unsigned char digit_pair_right[] = {
    DIGIT_TRASH,DIGIT_3435_R,DIGIT_3233_R,DIGIT_2531_R,
    DIGIT_2324_R,DIGIT_2122_R,DIGIT_1415_R,DIGIT_1213_R,
    DIGIT_11_R,DIGIT_N1N2_R,DIGIT_V1V2_R,DIGIT_M1M2_R,
    DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH
};

#define DIGIT_1415_SIGN     6
#define DIGIT_2324_SIGN     12
#define DIGIT_3435_SIGN     18
const unsigned char digit_pair_sign[] = {
    DIGIT_TRASH,DIGIT_3435_SIGN,DIGIT_TRASH,DIGIT_TRASH,
    DIGIT_2324_SIGN,DIGIT_TRASH,DIGIT_1415_SIGN,DIGIT_TRASH,
    DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH,
    DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH,DIGIT_TRASH
};

unsigned char blinking = 0;

