#include <Arduino.h>
/*
 Showing numbers, chars and phrases
                            A (segments[0] in this project)
                           ---
F (segments[5] in this project) |   | B (segments[1] in this project)
                          |   |
                           --- G (segments[6] in this project)
E (segments[4] in this project) |   |
                          |   | C (segments[2] in this project)
                           ---  . dot or dicimal (segments[7] in this project)
                            D (segments[3] in this project)
*/
#define SEG_A 2
#define SEG_B 5
#define SEG_C 8
#define SEG_D 9
#define SEG_E 4
#define SEG_F 3
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

void setState(bool mode) //sets the hole segment state to "mode"
{
    for (int seg: segments) {
        digitalWrite(seg, mode);
    }
}

void testAll() {
    for (int seg: segments) {
        delay(100);
        digitalWrite(seg, HIGH);
        delay(300);
        digitalWrite(seg, LOW);
    }
    for (byte i = 0; i <= 2; i++) {
        delay(100);
        setState(HIGH);
        delay(600);
        setState(LOW);
    }
}

void testAllFast() {
    for (int seg: segments) {
        delay(25);
        digitalWrite(seg, HIGH);
        delay(75);
        digitalWrite(seg, LOW);
    }
    for (byte i = 0; i <= 2; i++) {
        delay(25);
        setState(HIGH);
        delay(150);
        setState(LOW);
    }
}

void Print(char Char) // print any character on the segment ( Note : you can't use capital characters )
{
    int charNum = -1;// set search resault to -1
    setState(segMode);//turn off the segment
    for (byte i = 0; i < CHAR_COUNT; i++) {//search for the entered character
        if (Char == Chars[i][0]) {//if the character found
            charNum = i;//set the resault number into charNum ( because this function prints the character using it's number in the array )
        }
    }
    if (charNum == -1)// if the character not found
    {
        testAll();
    } else // else if the character found print it
    {
        for (byte i = 0; i < 7; i++) {
            digitalWrite(segments[i], Chars[charNum][i + 1]);
        }
    }
}

void Print(int num) // print any number on the segment
{
    setState(segMode);//turn off the segment
    if (num > CHAR_COUNT || num < 0)// if the number is not declared
    {
        testAll();
    } else // else if the number declared, print it
    {
        if (segMode == 0) { //for segment mode
            for (int i = 0; i < 8; i++) {
                digitalWrite(segments[i], Chars[num][i + 1]);
            }
        } else {
            for (int i = 0; i < 8; i++) {
                digitalWrite(segments[i], !Chars[num][i + 1]);
            }
        }
    }
}

void setup() {
    // set segment pins as OUTPUT
    pinMode(segments[0], OUTPUT);
    pinMode(segments[1], OUTPUT);
    pinMode(segments[2], OUTPUT);
    pinMode(segments[3], OUTPUT);
    pinMode(segments[4], OUTPUT);
    pinMode(segments[5], OUTPUT);
    pinMode(segments[6], OUTPUT);

    pinMode(6, OUTPUT);
    digitalWrite(6, LOW);
}

void loop() {
//    Print('8');
    testAllFast();


//    testAllFast();
}