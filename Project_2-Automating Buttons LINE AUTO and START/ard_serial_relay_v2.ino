#include <Arduino.h>

// Define relay pins
#define RELAY1 2
#define RELAY2 3
#define RELAY3 4
#define RELAY4 5

// Define LED status pins
#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

// Define command structure
struct Command {
    String name;
    int relayPin;
    int ledPin;
};

// Command mapping
Command commands[] = {
    {"LINE_AUTO", RELAY1, LED1},
    {"START", RELAY2, LED2},
    {"EXTRA", RELAY3, LED3},
    {"SPARE", RELAY4, LED4}
};

void setup() {
    Serial.begin(9600);

    // Set relay and LED pins as output
    for (int i = 0; i < 4; i++) {
        pinMode(commands[i].relayPin, OUTPUT);
        pinMode(commands[i].ledPin, OUTPUT);
        digitalWrite(commands[i].relayPin, HIGH);  // Active low (OFF)
        digitalWrite(commands[i].ledPin, LOW);     // Active high (OFF)
    }
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        processCommand(input);
    }
}

void processCommand(String cmd) {
    bool commandExecuted = false;

    for (int i = 0; i < 4; i++) {
        if (cmd == commands[i].name + "-ON") {
            digitalWrite(commands[i].relayPin, LOW);  // Turn relay ON
            digitalWrite(commands[i].ledPin, HIGH);   // Turn LED ON
            Serial.println("SUCCESS," + commands[i].name + " on");
            commandExecuted = true;
            break;
        }
        else if (cmd == commands[i].name + "-OFF") {
            digitalWrite(commands[i].relayPin, HIGH); // Turn relay OFF
            digitalWrite(commands[i].ledPin, LOW);    // Turn LED OFF
            Serial.println("SUCCESS," + commands[i].name + " off");
            commandExecuted = true;
            break;
        }
    }

    if (cmd == "ALL-ON") {
        for (int i = 0; i < 4; i++) {
            digitalWrite(commands[i].relayPin, LOW);
            digitalWrite(commands[i].ledPin, HIGH);
        }
        Serial.println("SUCCESS, all relays on");
        commandExecuted = true;
    }
    else if (cmd == "ALL-OFF") {
        for (int i = 0; i < 4; i++) {
            digitalWrite(commands[i].relayPin, HIGH);
            digitalWrite(commands[i].ledPin, LOW);
        }
        Serial.println("SUCCESS, all relays off");
        commandExecuted = true;
    }

    if (!commandExecuted) {
        Serial.println("ERROR, invalid command");
    }
}
