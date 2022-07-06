#include "Arduino.h"
#include "steer_wheel.h"

int currentSpeed = 0;

int prev_val_left = 1, prev_val_right = 1;
uint8_t val_left, val_right;
char temp[20];

struct can_frame canMsg;

void setup() {
    while (!Serial);
    Serial.begin(115200);

    Serial.println("Starting...");

    loadLCDDefault();

    /// NUMBER DISPLAY
    pinMode(segments[0], OUTPUT);
    pinMode(segments[1], OUTPUT);
    pinMode(segments[2], OUTPUT);
    pinMode(segments[3], OUTPUT);
    pinMode(segments[4], OUTPUT);
    pinMode(segments[5], OUTPUT);
    pinMode(segments[6], OUTPUT);

    Print(currentSpeed);

    /// CAN
    canMsg.can_id = 0x0F6;
    canMsg.can_dlc = 1;

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


void loop() {
    // Also invert them to make them normal LOW (they are normal HIGH by implementation)
    val_left = !digitalRead(LEFT_BUTTON_A);
    val_right = !digitalRead(RIGHT_BUTTON_A);

    if (prev_val_left != val_left || prev_val_right != val_right) {  // If something is different, update the display
        sprintf(temp, "    %d ---- %d    ", val_right, val_left); // Reverse them because the LCD is reversed
        lcd->setCursor(0, 0);
        lcd->print(temp);
    }

    if ((prev_val_left != val_left && val_left) || (prev_val_right != val_right && val_right)) {
        if (val_right) {  // TODO: Increase speed I think
            if(currentSpeed == 6) {
                prev_val_left = val_left;
                prev_val_right = val_right;
                return;
            }
            ++currentSpeed;
        } else if (val_left) {  // TODO: Decrease speed I think
            if(!currentSpeed) {
                prev_val_left = val_left;
                prev_val_right = val_right;
                return;
            }
            --currentSpeed;
        }
        Print(currentSpeed);

        canMsg.data[0] = (val_left << 1) | val_right;
        mcp2515->sendMessage(&canMsg);
        delay(500);
    }

    prev_val_left = val_left;
    prev_val_right = val_right;
}