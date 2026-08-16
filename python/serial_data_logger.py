import serial

# Serial port used by the ESP32.
# This must match the COM port shown in Arduino IDE.
SERIAL_PORT = "COM5"

# Baud rate used by the ESP32 Serial.begin() function.
# This must match Serial.begin(115200) in the ESP32 code.
BAUD_RATE = 115200


def main():
    # Print startup messages so the user knows the Python program has started.
    print("ESP32 serial reader started.")
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")

    try:
        # Open the ESP32 serial port.
        # The 'with' statement automatically closes the port when the program stops.
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as esp32:
            print("Connected to ESP32.")
            print("Reading serial data...\n")

            # Keep reading serial data until the user stops the program with Ctrl + C.
            while True:
                # Read one line from the ESP32.
                # decode() converts bytes into text.
                # strip() removes extra spaces and newline characters.
                line = esp32.readline().decode("utf-8", errors="ignore").strip()

                # Only print the line if it is not empty.
                if line:
                    print(line)

    except serial.SerialException as error:
        # This section runs if the serial connection fails.
        print("Serial connection error:")
        print(error)

        print("\nCheck that:")
        print("- The ESP32 is plugged in.")
        print("- The correct COM port is selected.")
        print("- Arduino Serial Monitor is closed.")
        print("- The baud rate matches the ESP32 code.")


# Run main() only when this file is executed directly.
if __name__ == "__main__":
    main()