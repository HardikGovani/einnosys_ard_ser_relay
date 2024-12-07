#include <EEPROM.h>

#define relay 7               // Relay connected to pin 7
#define led 13                // Status LED connected to pin 13
#define cmd_relay_on "ON"
#define cmd_relay_off "OFF"
#define cmd_relay_toggle "TOGGLE"
#define cmd_config_read "READ"
#define default_baud_rate 9600
#define valid_baud_rates {2400, 4800, 9600, 19200, 115200}

struct Config {
  char relayStatus[4];        // "ON" or "OFF"
  int baudRate;               // Baud rate
  float toggleTime;           // Toggle time in seconds
};

Config deviceConfig;          // Global configuration object

// Function to save configuration to EEPROM
void saveToEEPROM() {
  EEPROM.put(100, deviceConfig);
}

// Function to load configuration from EEPROM
void loadFromEEPROM() {
  EEPROM.get(100, deviceConfig);
  // Validate and set default if data is invalid
  if (deviceConfig.baudRate != 2400 && deviceConfig.baudRate != 4800 &&
      deviceConfig.baudRate != 9600 && deviceConfig.baudRate != 19200 &&
      deviceConfig.baudRate != 115200) {
    deviceConfig.baudRate = default_baud_rate;
  }
  if (deviceConfig.toggleTime < 0.1 || deviceConfig.toggleTime > 10.0) {
    deviceConfig.toggleTime = 1.0; // Default toggle time
  }
  if (strcmp(deviceConfig.relayStatus, "ON") != 0 && strcmp(deviceConfig.relayStatus, "OFF") != 0) {
    strcpy(deviceConfig.relayStatus, "OFF"); // Default relay status
  }
}

// Set relay and LED status based on the relay state
void updateRelayState() {
  if (strcmp(deviceConfig.relayStatus, "ON") == 0) {
    digitalWrite(relay, LOW);  // Relay ON (active low)
    digitalWrite(led, HIGH);  // LED ON
  } else if (strcmp(deviceConfig.relayStatus, "OFF") == 0) {
    digitalWrite(relay, HIGH); // Relay OFF
    digitalWrite(led, LOW);    // LED OFF
  }
}

// Toggle relay for a defined period
void toggleRelay(float duration) {
  digitalWrite(relay, LOW);
  digitalWrite(led, HIGH);
  delay(duration * 1000);
  digitalWrite(relay, HIGH);
  digitalWrite(led, LOW);
}

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  
  // Load settings from EEPROM
  loadFromEEPROM();

  // Set the relay and LED status based on the loaded state
  updateRelayState();

  // Initialize Serial with the loaded baud rate
  Serial.begin(deviceConfig.baudRate);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readString();
    command.trim(); // Remove leading/trailing whitespaces

    if (command == cmd_relay_on) {
      strcpy(deviceConfig.relayStatus, "ON");
      saveToEEPROM();
      updateRelayState();
      Serial.println("SUCCESS");
    } else if (command == cmd_relay_off) {
      strcpy(deviceConfig.relayStatus, "OFF");
      saveToEEPROM();
      updateRelayState();
      Serial.println("SUCCESS");
    } else if (command == cmd_relay_toggle) {
      toggleRelay(deviceConfig.toggleTime);
      Serial.println("SUCCESS");
    } else if (command.startsWith("bd,")) {
      int newBaudRate = command.substring(3).toInt();
      const int validBaudRates[] = valid_baud_rates;
      bool isValid = false;

      for (int i = 0; i < sizeof(validBaudRates) / sizeof(validBaudRates[0]); i++) {
        if (newBaudRate == validBaudRates[i]) {
          isValid = true;
          break;
        }
      }

      if (isValid) {
        deviceConfig.baudRate = newBaudRate;
        saveToEEPROM();
        Serial.begin(deviceConfig.baudRate); // Change baud rate
        Serial.println("SUCCESS");
      } else {
        Serial.println("FAILED");
      }
    } else if (command.startsWith("TGL,")) {
      float newToggleTime = command.substring(4).toFloat();
      if (newToggleTime >= 0.1 && newToggleTime <= 10.0) {
        deviceConfig.toggleTime = newToggleTime;
        saveToEEPROM();
        Serial.println("SUCCESS");
      } else {
        Serial.println("FAILED");
      }
    } else if (command == cmd_config_read) {
      Serial.print("RELAY-");
      Serial.print(deviceConfig.relayStatus);
      Serial.print(",BAUD-");
      Serial.print(deviceConfig.baudRate);
      Serial.print(",TTIME-");
      Serial.println(deviceConfig.toggleTime);
    } else {
      Serial.println("FAILED");
    }
  }
}
