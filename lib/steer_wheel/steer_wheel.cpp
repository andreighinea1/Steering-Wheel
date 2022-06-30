#include "steer_wheel.h"


/// NUMBER DISPLAY
const int segments[]{SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G}; // segment pins
const byte Chars[CHAR_COUNT][8]{
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
/// CAN
MCP2515 *mcp2515 = new MCP2515(10);
/// LCD
LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C(0x27, 16, 2);

/// NUMBER DISPLAY
void setSegmentNumberDisplayState(int seg, byte mode) // sets the hole segment state to "mode"
{
#ifdef COMMON_CATHODE
    digitalWrite(seg, mode);
#elif defined(COMMON_ANODE)
    digitalWrite(seg, !mode);
#endif
}

void setWholeNumberDisplayState(byte mode) //sets the whole number display state to "mode"
{
#ifdef COMMON_CATHODE
    for (int seg: segments) {
        digitalWrite(seg, mode);
    }
#elif defined(COMMON_ANODE)
    for (int seg: segments) {
        digitalWrite(seg, !mode);
    }
#endif
}

void Print(char Char) // print any character on the segment ( Note : you can't use capital characters )
{
    int num = -1; // set search result to -1
    setWholeNumberDisplayState(DISABLE_SEGMENT); //turn off the segment
    for (byte i = 0; i < CHAR_COUNT; i++) { //search for the entered character
        if (Char == Chars[i][0])
            num = i;
    }
    if (num == -1) { // if the character not found
//        testAllFast();
    } else { // else if the character found print it
        for (byte i = 0; i < 7; i++) {
            setSegmentNumberDisplayState(segments[i], Chars[num][i + 1]);
        }
    }
}

void Print(int num) // print any number on the segment
{
    setWholeNumberDisplayState(DISABLE_SEGMENT); //turn off the segment
    if (num > CHAR_COUNT || num < 0) { // if the number is not declared
//        testAllFast();
    } else { // else if the number declared, print it
        for (byte i = 0; i < 7; i++) {
            setSegmentNumberDisplayState(segments[i], Chars[num][i + 1]);
        }
    }
}

void testNumbers() {  // 5000 ms
    setWholeNumberDisplayState(DISABLE_SEGMENT);
    for (byte i = 0; i <= 9; i++) {
        Print(i);
        delay(500);
    }
}

void testAllFast() {  // 1225 ms
    setWholeNumberDisplayState(DISABLE_SEGMENT);
    for (int seg: segments) {  // 7 * 100 ms
        delay(25);
        digitalWrite(seg, ENABLE_SEGMENT);
        delay(75);
        digitalWrite(seg, DISABLE_SEGMENT);
    }
    for (byte i = 0; i <= 2; i++) {  // 3 * 175 ms
        delay(25);
        setWholeNumberDisplayState(ENABLE_SEGMENT);
        delay(150);
        setWholeNumberDisplayState(DISABLE_SEGMENT);
    }
}


/// LCD
void loadLCDDefault() {
    lcd->init();
    lcd->backlight();
    lcd->setCursor(0, 0);
    lcd->print(F("UPT Racing Team"));
}

