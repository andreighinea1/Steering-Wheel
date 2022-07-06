#include "Arduino.h"
#include <SPI.h>
#include "steer_wheel.h"

struct can_frame canMsg;

void setup() {
    while (!Serial);
    Serial.begin(115200);

    /// CAN
    canMsg.can_id = 0x0F6;
    canMsg.can_dlc = 1;

    mcp2515->reset();
    mcp2515->setBitrate(CAN_125KBPS);
    mcp2515->setNormalMode();

    Serial.println("------- CAN Read ----------");
}

int d;
void loop() {
    if (mcp2515->readMessage(&canMsg) == MCP2515::ERROR_OK) {
        d = canMsg.data[0];
        Serial.print("L=");
        Serial.print((d >> 1) & 1);
        Serial.print(" R=");
        Serial.println(d & 1);
    }
}