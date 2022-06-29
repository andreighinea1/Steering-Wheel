#include "steer_wheel.h"
#include "unity.h"


struct can_frame canMsg1;
struct can_frame canMsg2;
void setUp() {
    loadLCDDefault();

    /// NUMBER DISPLAY
    pinMode(segments[0], OUTPUT);
    pinMode(segments[1], OUTPUT);
    pinMode(segments[2], OUTPUT);
    pinMode(segments[3], OUTPUT);
    pinMode(segments[4], OUTPUT);
    pinMode(segments[5], OUTPUT);
    pinMode(segments[6], OUTPUT);

    /// CAN
    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 8;
    canMsg1.data[0] = 0x8E;
    canMsg1.data[1] = 0x87;
    canMsg1.data[2] = 0x32;
    canMsg1.data[3] = 0xFA;
    canMsg1.data[4] = 0x26;
    canMsg1.data[5] = 0x8E;
    canMsg1.data[6] = 0xBE;
    canMsg1.data[7] = 0x86;

    canMsg2.can_id = 0x036;
    canMsg2.can_dlc = 8;
    canMsg2.data[0] = 0x0E;
    canMsg2.data[1] = 0x00;
    canMsg2.data[2] = 0x00;
    canMsg2.data[3] = 0x08;
    canMsg2.data[4] = 0x01;
    canMsg2.data[5] = 0x00;
    canMsg2.data[6] = 0x00;
    canMsg2.data[7] = 0xA0;

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    /// SPEED BUTTONS
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    while (!Serial);
    Serial.begin(115200);

    /// ROW OF LEDs
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void tearDown() {
    // clean stuff up here
}

void test_numbers_display() {  // ~25000 ms
    Serial.println("1/4 - Starting test_numbers_display");
    for (int k = 0; k < 4; ++k) {  // 4 * 6225 ms
        testAllFast();
        testNumbers();
    }
}

void test_can_messages() {  // 5000 ms
    Serial.println("2/4 - Starting test_can_messages");
    for (int k = 0; k < 50; ++k) {
        mcp2515.sendMessage(&canMsg1);
        mcp2515.sendMessage(&canMsg2);
        delay(100);
    }
}

void test_speed_buttons() {  // 25000 ms
    Serial.println("3/4 - Starting test_speed_buttons");
    for (int k = 0; k < 100; ++k) {
        Serial.print("A0: ");
        Serial.println(digitalRead(A0));
        Serial.print("A1: ");
        Serial.println(digitalRead(A1));  // TODO: This one is not working !!!!
        //Serial.println("");
        delay(250);
    }
}

void test_row_of_LEDs() {  // 15300 ms
    Serial.println("4/4 - Starting test_row_of_LEDs");
    for (int k = 0; k < 6; ++k) {
        // Fading the LED
        for (int i = 0; i < 255; i++) {
            analogWrite(LED_PIN, i);
            delay(5);
        }
        for (int i = 255; i > 0; i--) {
            analogWrite(LED_PIN, i);
            delay(5);
        }
    }
}

int runUnityTests() {
    UNITY_BEGIN();
    RUN_TEST(test_numbers_display); // ~25000 ms
    RUN_TEST(test_can_messages);  // 5000 ms
    RUN_TEST(test_speed_buttons);  // 25000 ms
    RUN_TEST(test_row_of_LEDs);  // 15300 ms

    Serial.println("DONE");
    return UNITY_END();
}

void setup() {  // TOTAL: ~72500 ms
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}

void loop() {}