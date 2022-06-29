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
#define COMMON_CATHODE 0
//#define COMMON_ANODE 1
bool segMode = COMMON_CATHODE; // set this to your segment type, my segment is common_cathode
int segments[]{SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G}; // segment pins
#define CHAR_COUNT 16
byte Chars[CHAR_COUNT][8]{
        {'0', 1, 1, 1, 1, 1, 1, 0},//0
        {'1', 0, 1, 1, 0, 0, 0, 0},//1
        {'2', 1, 1, 0, 1, 1, 0, 1},//2
        {'3', 1, 1, 1, 1, 0, 0, 1},//3
        {'4', 0, 1, 1, 0, 0, 1, 1},//4
        {'5', 1, 0, 1, 1, 0, 1, 1},//5
        {'6', 1, 0, 1, 1, 1, 1, 1},//6
        {'7', 1, 1, 1, 0, 0, 0, 0},//7
        {'8', 1, 1, 1, 1, 1, 1, 1},//8
        {'9', 1, 1, 1, 1, 0, 1, 1},//9
        {'a', 1, 1, 1, 0, 1, 1, 1},//A/10
        {'b', 0, 0, 1, 1, 1, 1, 1},//b/11
        {'c', 1, 0, 0, 1, 1, 1, 0},//C/12
        {'d', 0, 1, 1, 1, 1, 0, 1},//d/13
        {'e', 1, 0, 0, 1, 1, 1, 1},//E/14
        {'f', 1, 0, 0, 0, 1, 1, 1},//F/15
};

void setNumberDisplayState(bool mode);
void testNumbers();
void testAllFast();
void Print(char Char); // print any character on the segment ( Note : you can't use capital characters )
void Print(int num); // print any number on the segment

/// CAN
MCP2515 mcp2515(10);

/// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
void loadLCDDefault();

/// ROW OF LEDS
#define LED_PIN 6

#endif //STEERWHEEL_MAIN_H
