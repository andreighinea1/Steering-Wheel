#include <Arduino.h>
#include "mcp2515.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"


void Print(char Char);
void Print(int num);

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

void setState(bool mode) //sets the hole segment state to "mode"
{
    for (int seg: segments) {
        digitalWrite(seg, mode);
    }
}

void testAll() {
    setState(segMode);
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

void testNumbers() {
    setState(segMode);
    for (byte i = 0; i <= 9; i++) {
        Print(i);
        delay(500);
    }
}

void testAllFast() {
    setState(segMode);
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
    int charNum = -1; // set search result to -1
    setState(segMode); //turn off the segment
    for (byte i = 0; i < CHAR_COUNT; i++) { //search for the entered character
        if (Char == Chars[i][0])
            charNum = i;
    }
    if (charNum == -1) { // if the character not found
        testAll();
    } else { // else if the character found print it
        for (byte i = 0; i < 7; i++) {
            digitalWrite(segments[i], Chars[charNum][i + 1]);
        }
    }
}

void Print(int num) // print any number on the segment
{
    setState(segMode); //turn off the segment
    if (num > CHAR_COUNT || num < 0) { // if the number is not declared
        testAll();
    } else { // else if the number declared, print it
        if (segMode == 0) { //for segment mode TODO: Make this with #ifdef to save code space
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

/// TESTS FOR NUMBER DISPLAY
//void setup() {
//    // set segment pins as OUTPUT
//    pinMode(segments[0], OUTPUT);
//    pinMode(segments[1], OUTPUT);
//    pinMode(segments[2], OUTPUT);
//    pinMode(segments[3], OUTPUT);
//    pinMode(segments[4], OUTPUT);
//    pinMode(segments[5], OUTPUT);
//    pinMode(segments[6], OUTPUT);
//
//    pinMode(6, OUTPUT);
//    digitalWrite(6, LOW);
//}
//
//void loop() {
//    // Print('8');
//    testAllFast();
//    testNumbers();
//}


/// TESTS FOR CAN
//struct can_frame canMsg1;
//struct can_frame canMsg2;
//MCP2515 mcp2515(10);
//
//
//void setup() {
//    pinMode(6, OUTPUT);
//    digitalWrite(6, LOW);
//
//    canMsg1.can_id  = 0x0F6;
//    canMsg1.can_dlc = 8;
//    canMsg1.data[0] = 0x8E;
//    canMsg1.data[1] = 0x87;
//    canMsg1.data[2] = 0x32;
//    canMsg1.data[3] = 0xFA;
//    canMsg1.data[4] = 0x26;
//    canMsg1.data[5] = 0x8E;
//    canMsg1.data[6] = 0xBE;
//    canMsg1.data[7] = 0x86;
//
//    canMsg2.can_id  = 0x036;
//    canMsg2.can_dlc = 8;
//    canMsg2.data[0] = 0x0E;
//    canMsg2.data[1] = 0x00;
//    canMsg2.data[2] = 0x00;
//    canMsg2.data[3] = 0x08;
//    canMsg2.data[4] = 0x01;
//    canMsg2.data[5] = 0x00;
//    canMsg2.data[6] = 0x00;
//    canMsg2.data[7] = 0xA0;
//
//    while (!Serial);
//    Serial.begin(115200);
//
//    mcp2515.reset();
//    mcp2515.setBitrate(CAN_125KBPS);
//    mcp2515.setNormalMode();
//
//    Serial.println("Example: Write to CAN");
//}
//
//void loop() {
//    mcp2515.sendMessage(&canMsg1);
//    mcp2515.sendMessage(&canMsg2);
//
//    Serial.println("Messages sent");
//
//    delay(100);
//}


/// TESTS FOR ANALOG PINS
//void setup() {
//    pinMode(6, OUTPUT);
//    digitalWrite(6, LOW);
//
//    pinMode(A0, INPUT);
//    pinMode(A1, INPUT);
//
//    while (!Serial);
//    Serial.begin(115200);
//}
//
//void loop() {
//    Serial.print("A0: ");
//    Serial.println(digitalRead(A0));
//    Serial.print("A1: ");
//    Serial.println(digitalRead(A1));  // TODO: This one is not working !!!!
//    //Serial.println("");
//    delay(250);
//}


/// LCD
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//
//void setup() {
//    pinMode(6, OUTPUT);
//    digitalWrite(6, LOW);
//
//    lcd.init();
//    lcd.backlight();
//    lcd.setCursor(0, 0);
//    lcd.print("UPT Racing Team");
//}
//
//void loop() {
//
//}


/// ROW OF LEDs
#define LED_PIN 6
void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    //Fading the LED
    for(int i=0; i<255; i++){
        analogWrite(LED_PIN, i);
        delay(5);
    }
    for(int i=255; i>0; i--){
        analogWrite(LED_PIN, i);
        delay(5);
    }
}