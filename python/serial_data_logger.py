import csv
from datetime import datetime
from pathlib import Path

import serial

# Serial port used by the ESP32.
# This must match the COM port shown in Arduino IDE.
SERIAL_PORT = "COM5"

# Baud rate used by the ESP32 Serial.begin() function.
# This must match Serial.begin(115200) in the ESP32 code.
BAUD_RATE = 115200

# CSV file path.
# The file will be saved inside the project data folder.
PROJECT_ROOT = Path(__file__).resolve().parent.parent
CSV_FILE_PATH = PROJECT_ROOT / "data" / "serial_log.csv"

CSV_HEADER = [
    "timestamp",
    "ldr_value",
    "light_condition",
    "alarm_status",
    "alarm_switch",
    "led_switch",
    "buzzer_switch",
    "led_output",
    "buzzer_output",
]


def create_csv_file_if_needed():
    # Create the data folder if it does not already exist.
    CSV_FILE_PATH.parent.mkdir(exist_ok=True)

    # If the CSV file does not exist, create it and write the header row.
    if CSV_FILE_PATH.exists() == False:
        with open(CSV_FILE_PATH, mode="w", newline="", encoding="utf-8") as csv_file:
            writer = csv.writer(csv_file)
            writer.writerow(CSV_HEADER)


def save_data_to_csv(row_data):
    # Open the CSV file in append mode and add one new row.
    with open(CSV_FILE_PATH, mode="a", newline="", encoding="utf-8") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(row_data)


def process_data_line(line):
    # Split the DATA line into separate values using commas.
    parts = line.split(",")

    # A valid DATA line should contain 9 fields:
    # DATA,LDR value,Light condition,Alarm status,Alarm switch,LED switch,Buzzer switch,LED output,Buzzer output
    if len(parts) != 9:
        print("Invalid DATA line:")
        print(line)
        return

    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    ldr_value = parts[1]
    light_condition = parts[2]
    alarm_status = parts[3]
    alarm_switch = parts[4]
    led_switch = parts[5]
    buzzer_switch = parts[6]
    led_output = parts[7]
    buzzer_output = parts[8]

    row_data = [
        timestamp,
        ldr_value,
        light_condition,
        alarm_status,
        alarm_switch,
        led_switch,
        buzzer_switch,
        led_output,
        buzzer_output,
    ]

    save_data_to_csv(row_data)

    print("Saved DATA row:")
    print(row_data)


def main():
    print("ESP32 serial data logger started.")
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")
    print(f"CSV file: {CSV_FILE_PATH}")

    create_csv_file_if_needed()

    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as esp32:
            print("Connected to ESP32.")
            print("Reading and saving DATA lines...\n")

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