import serial

# Serial port used by the ESP32.
# This must match the COM port shown in Arduino IDE.
SERIAL_PORT = "COM5"

# Baud rate used by the ESP32 Serial.begin() function.
# This must match Serial.begin(115200) in the ESP32 code.
BAUD_RATE = 115200


def process_data_line(line):
    # Split the DATA line into separate values using commas.
    parts = line.split(",")

    # A valid DATA line should contain 9 fields:
    # DATA,LDR value,Light condition,Alarm status,Alarm switch,LED switch,Buzzer switch,LED output,Buzzer output
    if len(parts) != 9:
        print("Invalid DATA line:")
        print(line)
        return

    ldr_value = parts[1]
    light_condition = parts[2]
    alarm_status = parts[3]
    alarm_switch = parts[4]
    led_switch = parts[5]
    buzzer_switch = parts[6]
    led_output = parts[7]
    buzzer_output = parts[8]

    print("----- ESP32 DATA -----")
    print(f"LDR value: {ldr_value}")
    print(f"Light condition: {light_condition}")
    print(f"Alarm status: {alarm_status}")
    print(f"Alarm switch: {alarm_switch}")
    print(f"LED switch: {led_switch}")
    print(f"Buzzer switch: {buzzer_switch}")
    print(f"LED output: {led_output}")
    print(f"Buzzer output: {buzzer_output}")


def main():
    print("ESP32 serial reader started.")
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")

    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as esp32:
            print("Connected to ESP32.")
            print("Reading DATA lines...\n")

            while True:
                line = esp32.readline().decode("utf-8", errors="ignore").strip()

                if line.startswith("DATA,"):
                    process_data_line(line)

    except serial.SerialException as error:
        print("Serial connection error:")
        print(error)

        print("\nCheck that:")
        print("- The ESP32 is plugged in.")
        print("- The correct COM port is selected.")
        print("- Arduino Serial Monitor is closed.")
        print("- The baud rate matches the ESP32 code.")


if __name__ == "__main__":
    main()