from pylibftdi import Driver, BitBangDevice

# Function to get the FTDI device ID dynamically
def get_ftdi_device_id():
    print("Searching for connected FTDI devices...")
    devices = list(Driver().list_devices())
    if len(devices) == 0:
        print("No FTDI devices found. Please connect a device and try again.")
        exit()
    # Extract the device ID (assuming the first device is used)
    device_id = devices[0][2]
    print(f"FTDI device found: {device_id}")
    return device_id

# Relay ON/OFF commands based on your logic
relay_on_cmds = [0x80, 0x20, 0x08, 0x02]
relay_off_cmds = [0x7F, 0xDF, 0xF7, 0xFD]

# Relay mapping for readable names
relay_mapping = {
    "LINE_AUTO": 1,  # Relay 1
    "START": 2,      # Relay 2
    "RELAY-3": 3,    # Relay 3
    "RELAY-4": 4     # Relay 4
}

# Initialize the FTDI device
try:
    BitBangDeviceID = get_ftdi_device_id()  # Get the device ID dynamically
    bb = BitBangDevice(BitBangDeviceID)  # Use the dynamic device ID
    bb.direction = 0xFF  # Set all 8 I/O pins as output
    print("Relay controller initialized.")
except Exception as e:
    print(f"Error initializing FTDI device: {e}")
    exit()

# Function to turn ON a relay
def relay_on(relay_name):
    if relay_name in relay_mapping:
        relay_index = relay_mapping[relay_name]
        bb.port |= relay_on_cmds[relay_index - 1]
        return f"SUCCESS-{relay_name} ON"
    else:
        return f"FAILURE-{relay_name} ON"

# Function to turn OFF a relay
def relay_off(relay_name):
    if relay_name in relay_mapping:
        relay_index = relay_mapping[relay_name]
        bb.port &= relay_off_cmds[relay_index - 1]
        return f"SUCCESS-{relay_name} OFF"
    else:
        return f"FAILURE-{relay_name} OFF"

# Function to turn all relays ON
def all_on():
    for relay_index in range(1, 5):  # Relay indices 1 to 4
        bb.port |= relay_on_cmds[relay_index - 1]
    return "SUCCESS-ALL relays ON"

# Function to turn all relays OFF
def all_off():
    for relay_index in range(1, 5):  # Relay indices 1 to 4
        bb.port &= relay_off_cmds[relay_index - 1]
    return "SUCCESS-ALL relays OFF"

# Function to execute commands dynamically
def execute_command(command):
    if command == "LINE_AUTO-ON":
        return relay_on("LINE_AUTO")
    elif command == "LINE_AUTO-OFF":
        return relay_off("LINE_AUTO")
    elif command == "START-ON":
        return relay_on("START")
    elif command == "START-OFF":
        return relay_off("START")
    elif command == "RELAY-3-ON":
        return relay_on("RELAY-3")
    elif command == "RELAY-3-OFF":
        return relay_off("RELAY-3")
    elif command == "RELAY-4-ON":
        return relay_on("RELAY-4")
    elif command == "RELAY-4-OFF":
        return relay_off("RELAY-4")
    elif command == "ALL-ON":
        return all_on()
    elif command == "ALL-OFF":
        return all_off()
    else:
        return f"FAILURE-Invalid command: {command}"

# Main loop to process commands
try:
    while True:
        command = input("Enter command: ").strip().upper()
        result = execute_command(command)
        print(result)
        if command == "EXIT":
            print("Exiting relay controller.")
            break

except KeyboardInterrupt:
    print("\nExiting relay controller.")

finally:
    bb.close()
    print("Relay controller closed.")
