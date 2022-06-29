#ifndef STEERWHEEL_MAIN_H
#define STEERWHEEL_MAIN_H

#include <Arduino.h>
#include "mcp2515.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

/// NUMBER DISPLAY
/*
 Showing numbers, chars and phrases
                 SEG_A
               ---------
              |         |
        SEG_F |         | SEG_B
              |         |
               ---------  SEG_G
              |         |
        SEG_E |         | SEG_C
              |         |
               ---------   . dot (not used)
                 SEG_D
*/
#define SEG_A 9
#define SEG_B 4
#define SEG_C 3
#define SEG_D 2
#define SEG_E 5
#define SEG_F 8
#define SEG_G 7
#define CHAR_COUNT 16
#define DISABLE_SEGMENT LOW
#define ENABLE_SEGMENT HIGH
// set this to your segment type, my segment is COMMON_CATHODE
#define COMMON_CATHODE 0
//#define COMMON_ANODE 1

void setSegmentNumberDisplayState(int seg, byte mode);
void setWholeNumberDisplayState(byte mode);
void testNumbers();
void testAllFast();
void Print(char Char); // print any character on the segment ( Note : you can't use capital characters )
void Print(int num); // print any number on the segment

extern int segments[]; // segment pins
extern byte Chars[CHAR_COUNT][8];

/// CAN
extern MCP2515 *mcp2515;

/// LCD
extern LiquidCrystal_I2C *lcd;
void loadLCDDefault();

/// ROW OF LEDS
#define LED_PIN 6

#endif //STEERWHEEL_MAIN_H
