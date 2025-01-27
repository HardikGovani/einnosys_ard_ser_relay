# Arduino Relay Control System

This project provides an Arduino-based solution to automate the operation of relays replacing physical push buttons with serial commands. The system is designed to control four relays via serial communication.

## Features
- Control four relays using serial commands.
- Status indication via LEDs.
- Ensures relays are OFF by default upon power failure.
- Provides serial feedback for successful command execution.

## Hardware Requirements
- Arduino Board
- 4-Channel Relay Module (Active LOW)
- 4 LEDs for status indication
- USB Cable for serial communication
- Power Supply (5V)

## Pin Configuration
| Relay   | GPIO Pin | LED Pin |
|---------|---------|---------|
| LINE_AUTO | 2       | 6       |
| START     | 3       | 7       |
| EXTRA     | 4       | 8       |
| SPARE     | 5       | 9       |

## Serial Command Format
Commands should be sent over serial at **9600 baud rate**, and must follow the format:

- `LINE_AUTO-ON` - Turns on relay 1
- `LINE_AUTO-OFF` - Turns off relay 1
- `START-ON` - Turns on relay 2
- `START-OFF` - Turns off relay 2
- `EXTRA-ON` - Turns on relay 3
- `EXTRA-OFF` - Turns off relay 3
- `SPARE-ON` - Turns on relay 4
- `SPARE-OFF` - Turns off relay 4
- `ALL-ON` - Turns on all relays
- `ALL-OFF` - Turns off all relays

## Serial Responses
The system provides responses for each command execution:

Example responses:
- `SUCCESS, LINE_AUTO on`
- `SUCCESS, START off`
- `ERROR, invalid command`

## Troubleshooting
- Ensure the correct COM port is selected in Arduino IDE.
- Verify relay connections and power supply.
- Check for command spelling errors.

---

For any queries, feel free to contact us at support@sunrobotics.in
