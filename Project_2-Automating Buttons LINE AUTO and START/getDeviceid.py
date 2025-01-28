from pylibftdi import Driver

print("Connected FTDI devices:")
for device in Driver().list_devices():
    print(device) 