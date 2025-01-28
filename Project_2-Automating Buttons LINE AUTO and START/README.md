# USB Relay Controller Setup and Operation

## Introduction
This guide explains how to set up and operate the USB relay controller using Python on both Windows (tested) and Linux platforms. The process includes installing required drivers, setting up the environment, and running the provided Python scripts for relay operation.

---

## **Windows Setup (Tested)**

### **Step 1: Install FTDI Drivers**
1. Download FTDI drivers from the following link: [FTDI VCP Drivers](https://ftdichip.com/drivers/vcp-drivers/).
2. Select the appropriate version for your system:
   - **32-bit:** [Download 32-bit Driver](https://ftdichip.com/wp-content/uploads/2023/09/CDM-v2.12.36.4-WHQL-Certified.zip)
   - **64-bit:** [Download 64-bit Driver](https://ftdichip.com/wp-content/uploads/2023/09/CDM-v2.12.36.4-WHQL-Certified.zip)
3. Extract the downloaded ZIP file and install the driver.

### **Step 2: Replace FT232R USB UART Driver**
1. Download Zadig from the official website: [Zadig](https://zadig.akeo.ie/).
   - Direct download link: [Download Zadig](https://github.com/pbatard/libwdi/releases/download/v1.5.1/zadig-2.9.exe)
2. Run Zadig as an administrator.
3. Follow these steps:
   - **Connect the USB Relay Board** to your computer.
   - In Zadig, click `Options > List All Devices`.
   - Select the `FT232R USB UART` device.
   - Replace the driver with **libusbK driver**.
4. Verify the installation:
   - Open **Device Manager**.
   - Ensure the device appears under the `libusbK` category as `USB Device`.

### **Step 3: Install Required DLLs**
1. The required DLLs (`libusb-1.0` and `libftdi1.dll`) are included in the `src` folder.
2. Copy these DLLs to a directory, e.g., `C:\Python312\libftdi`.
3. Add the directory to the system's environment variable:
   - **Steps to add path to system variables**:
     1. Right-click `This PC` or `My Computer` and select `Properties`.
     2. Click `Advanced System Settings` > `Environment Variables`.
     3. Under `System Variables`, find `Path` and click `Edit`.
     4. Add the path `C:\Python312\libftdi`.
     5. Click `OK` to save and restart your system if necessary.

### **Step 4: Install Python Dependencies**
1. Install `pylibftdi` via `pip`. Run the following command based on your Python version:
   ```bash
   pip install pylibftdi
   ```
2. Verify installation:
   - Check if `pylibftdi` is installed in the Python site-packages directory.

### **Step 5: Verify the USB Relay Device**
1. Run the `getDeviceid.py` script to check connected FTDI devices:
   ```python
   from pylibftdi import Driver

   print("Connected FTDI devices:")
   for device in Driver().list_devices():
       print(device)
   ```
2. If no devices are listed, revisit the driver installation steps or verify the DLL path.

### **Step 6: Operate the Relay**
1. Run the `sample_app.py` script to control the relays dynamically.
2. Key commands to control relays:
   - **Relay 1 (LINE_AUTO)**:
     - `LINE_AUTO-ON`: Turn ON relay 1.
     - `LINE_AUTO-OFF`: Turn OFF relay 1.
   - **Relay 2 (START)**:
     - `START-ON`: Turn ON relay 2.
     - `START-OFF`: Turn OFF relay 2.
   - **Relay 3 (RELAY-3)**:
     - `RELAY-3-ON`: Turn ON relay 3.
     - `RELAY-3-OFF`: Turn OFF relay 3.
   - **Relay 4 (RELAY-4)**:
     - `RELAY-4-ON`: Turn ON relay 4.
     - `RELAY-4-OFF`: Turn OFF relay 4.
   - **All Relays**:
     - `ALL-ON`: Turn ON all relays.
     - `ALL-OFF`: Turn OFF all relays.
3. Exit the application by typing `EXIT`.

---

## **Linux Setup**

### **Step 1: Install Python and Dependencies**
1. Ensure Python is installed on your system.
2. Install `pylibftdi` using:
   ```bash
   pip install pylibftdi
   ```

### **Step 2: Install Required Drivers**
- Replace the existing FTDI driver with the `libusbK` driver for Linux.
- (Download Linux driver same as per the windows driver links.)

### **Step 3: Verify the Device**
1. Run the `getDeviceid.py` script to check connected FTDI devices.

### **Step 4: Operate the Relay**
- Follow the same steps as in the Windows setup to run the `sample_app.py` script.

---

## **Support and Troubleshooting**
1. **Driver Issues**:
   - Ensure the driver is installed correctly.
   - Restart the system after making changes to the environment variables.

2. **FTDI Device Not Detected**:
   - Verify the connection in **Device Manager** (Windows) or `lsusb` (Linux).

3. **Python Errors**:
   - Check the Python version and site-packages directory for `pylibftdi`.
   - Reinstall dependencies if necessary.

---

## **Repository Contents**
- **`getDeviceid.py`**: Script to verify connected FTDI devices.
- **`sample_app.py`**: Main application to control the USB relay.
- **`src`**: Contains required DLL files (`libusb-1.0` and `libftdi1.dll`).

---

Feel free to reach out for additional support or clarification!
