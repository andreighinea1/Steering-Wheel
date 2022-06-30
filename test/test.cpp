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

    mcp2515->reset();
    mcp2515->setBitrate(CAN_125KBPS);
    mcp2515->setNormalMode();

    /// SPEED BUTTONS
    pinMode(LEFT_BUTTON_A, INPUT);
    pinMode(RIGHT_BUTTON_A, INPUT);

    /// ROW OF LEDs
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void tearDown() {
    // clean stuff up here
}

void test_numbers_display() {  // ~12500 ms
    TEST_MESSAGE("1/4 - Starting test_numbers_display");
    for (int k = 0; k < 4; ++k) {  // 4 * 6225 ms
        testAllFast();
        testNumbers();
    }
    setWholeNumberDisplayState(DISABLE_SEGMENT);
}

void test_can_messages() {  // 5000 ms
    TEST_MESSAGE("2/4 - Starting test_can_messages");
    for (int k = 0; k < 50; ++k) {
        mcp2515->sendMessage(&canMsg1);
        mcp2515->sendMessage(&canMsg2);
        delay(100);
    }
}

void test_speed_buttons() {  // 25000 ms
//[[noreturn]] void test_speed_buttons() {  // 25000 ms
    int prev_val_left = -1, prev_val_right = -1;
    int val_left, val_right;
    char temp[20];

    TEST_MESSAGE("3/4 - Starting test_speed_buttons");
    for (int k = 0; k < 500; ++k) {
//    while (true) {
        val_left = digitalRead(LEFT_BUTTON_A);  // TODO: This one is not working !!!!
        val_right = digitalRead(RIGHT_BUTTON_A);

        if (prev_val_left != val_left || prev_val_right != val_right) {
            sprintf(temp, "    %d ---- %d    ", val_left, val_right);
            lcd->setCursor(0, 0);
            lcd->print(temp);

            prev_val_left = val_left;
            prev_val_right = val_right;
        }
    }
}

void test_row_of_LEDs() {  // 15300 ms
    TEST_MESSAGE("4/4 - Starting test_row_of_LEDs");
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
    RUN_TEST(test_numbers_display); // ~12500 ms
    RUN_TEST(test_can_messages);  // 5000 ms
    RUN_TEST(test_speed_buttons);  // 25000 ms
    RUN_TEST(test_row_of_LEDs);  // 15300 ms

    TEST_MESSAGE("DONE\n");
    return UNITY_END();
}

void setup() {  // TOTAL: ~71000 ms
    loadLCDDefault();

    delay(500);

    runUnityTests();
}

void loop() {}