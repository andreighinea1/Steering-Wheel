#include <Arduino.h>
#include "mcp2515.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "steer_wheel.h"

/// NUMBER DISPLAY
void setNumberDisplayState(bool mode) //sets the hole segment state to "mode"
{
    for (int seg: segments) {
        digitalWrite(seg, mode);
    }
}

void Print(char Char) // print any character on the segment ( Note : you can't use capital characters )
{
    int charNum = -1; // set search result to -1
    setNumberDisplayState(segMode); //turn off the segment
    for (byte i = 0; i < CHAR_COUNT; i++) { //search for the entered character
        if (Char == Chars[i][0])
            charNum = i;
    }
    if (charNum == -1) { // if the character not found
        testAllFast();
    } else { // else if the character found print it
        for (byte i = 0; i < 7; i++) {
            digitalWrite(segments[i], Chars[charNum][i + 1]);
        }
    }
}

void Print(int num) // print any number on the segment
{
    setNumberDisplayState(segMode); //turn off the segment
    if (num > CHAR_COUNT || num < 0) { // if the number is not declared
        testAllFast();
    } else { // else if the number declared, print it
        if (segMode == 0) { //for segment mode TODO: Make this with #ifdef to save code space
            for (int i = 0; i < 7; i++) {
                digitalWrite(segments[i], Chars[num][i + 1]);
            }
        } else {
            for (int i = 0; i < 7; i++) {
                digitalWrite(segments[i], !Chars[num][i + 1]);
            }
        }
    }
}

void testNumbers() {  // 5000 ms
    setNumberDisplayState(segMode);
    for (byte i = 0; i <= 9; i++) {
        Print(i);
        delay(500);
    }
}

void testAllFast() {  // 1225 ms
    setNumberDisplayState(segMode);
    for (int seg: segments) {  // 7 * 100 ms
        delay(25);
        digitalWrite(seg, HIGH);
        delay(75);
        digitalWrite(seg, LOW);
    }
    for (byte i = 0; i <= 2; i++) {  // 3 * 175 ms
        delay(25);
        setNumberDisplayState(HIGH);
        delay(150);
        setNumberDisplayState(LOW);
    }
}


/// LCD
void loadLCDDefault() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("UPT Racing Team");
}

