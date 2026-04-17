#include <Arduino.h>
#include <Bluepad32.h>

// Store connected controller
GamepadPtr myGamepad = nullptr;

// Callback when controller connects
void onConnectedGamepad(GamepadPtr gp) {
    Serial.println("Controller connected!");
    myGamepad = gp;
}

// Callback when controller disconnects
void onDisconnectedGamepad(GamepadPtr gp) {
    Serial.println("Controller disconnected!");
    if (myGamepad == gp) {
        myGamepad = nullptr;
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Starting Bluepad32...");

    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);

    // Optional: clear previous pairings
    BP32.forgetBluetoothKeys();
}

void loop() {
    // Update controller state
    BP32.update();

    if (myGamepad && myGamepad->isConnected()) {

        // Check X button (Cross on PS4)
        if (myGamepad->a()) {
            Serial.println("X pressed");
        }
    }

    delay(50);
}