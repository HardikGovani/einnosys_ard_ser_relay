# Arduino Serial Relay Control - Version 1 (`ard_ser_relay_v1`)

This project provides a complete solution for controlling a relay module via serial commands using an Arduino. The relay state is retained across power cycles, and users can customize baud rate and toggle timing.

## Features
- Serial-based control with predefined commands:
  - `ON`: Turn the relay on.
  - `OFF`: Turn the relay off.
  - `TOGGLE`: Toggle the relay state for a defined duration.
  - `bd,rate`: Update the communication baud rate.
  - `TGL,time`: Set the toggle duration (0.1–10 seconds).
  - `READ`: Retrieve current configuration settings.
- Stores settings in EEPROM to retain state across power cycles.
- Status LED on pin 13 to indicate relay state.

## Commands
| Command       | Description                                                                           |
|---------------|---------------------------------------------------------------------------------------|
| `ON`          | Turns the relay ON and updates the LED status.                                       |
| `OFF`         | Turns the relay OFF and updates the LED status.                                      |
| `TOGGLE`      | Toggles the relay state for the defined time in seconds (single cycle).              |
| `bd,rate`     | Updates the baud rate for serial communication (valid: 2400, 4800, 9600, 19200, 115200). |
| `TGL,time`    | Sets the toggle duration in seconds (valid range: 0.1–10).                          |
| `READ`        | Outputs current configuration in a comma-separated format. Example: `RELAY-OFF,BAUD-9600,TTIME-1`. |

## Setup
1. Connect the relay module to pin 7 (active low).
2. Connect the status LED to pin 13.
3. Upload the provided code to your Arduino.
4. Open the serial monitor, set the baud rate (default: 9600), and test commands.

## Configuration Retention
- The relay state, baud rate, and toggle time are saved in EEPROM.
- On startup, the last saved configuration is loaded automatically.

## Requirements
- Arduino board (e.g., UNO, Nano).
- Relay module (active low).
- Status LED.
- Serial communication software (e.g., Arduino Serial Monitor).

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ard_ser_relay_v1.git
