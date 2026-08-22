"""
Plot ESP32 light sensor data saved by serial_data_logger.py.

The program reads:
    data/serial_log.csv

If serial_log.csv is unavailable, it uses:
    data/sample_serial_log.csv

The completed chart is saved as:
    data/serial_log_plot.png
"""

import csv
from datetime import datetime
from pathlib import Path

import matplotlib.pyplot as plt


# The project root is one folder above this Python file.
PROJECT_ROOT = Path(__file__).resolve().parent.parent

DATA_FOLDER = PROJECT_ROOT / "data"
SERIAL_LOG_FILE = DATA_FOLDER / "serial_log.csv"
SAMPLE_LOG_FILE = DATA_FOLDER / "sample_serial_log.csv"
OUTPUT_IMAGE_FILE = DATA_FOLDER / "serial_log_plot.png"

# This should match the threshold used in the ESP32 program.
ALARM_THRESHOLD = 2000


def choose_csv_file():
    """
    Use the real serial log when available.
    Otherwise, use the sample data file.
    """
    if SERIAL_LOG_FILE.exists():
        return SERIAL_LOG_FILE

    if SAMPLE_LOG_FILE.exists():
        return SAMPLE_LOG_FILE

    raise FileNotFoundError(
        "No CSV data file was found.\n"
        "Expected data/serial_log.csv or data/sample_serial_log.csv."
    )


def load_csv_data(csv_file_path):
    """
    Read timestamps, LDR values, and alarm states from the CSV file.
    """
    timestamps = []
    ldr_values = []
    alarm_timestamps = []
    alarm_values = []

    with open(csv_file_path, mode="r", newline="", encoding="utf-8-sig") as csv_file:
        reader = csv.DictReader(csv_file)

        required_columns = {"timestamp", "ldr_value", "alarm_status"}

        if reader.fieldnames is None:
            raise ValueError("The CSV file does not contain a header row.")

        missing_columns = required_columns - set(reader.fieldnames)

        if missing_columns:
            raise ValueError(
                "The CSV file is missing these columns: "
                + ", ".join(sorted(missing_columns))
            )

        for row_number, row in enumerate(reader, start=2):
            try:
                timestamp = datetime.strptime(
                    row["timestamp"],
                    "%Y-%m-%d %H:%M:%S",
                )

                ldr_value = int(row["ldr_value"])
                alarm_status = row["alarm_status"].strip()

            except (ValueError, TypeError):
                print(f"Skipped invalid CSV row {row_number}.")
                continue

            timestamps.append(timestamp)
            ldr_values.append(ldr_value)

            # Alarm status may be written as "Alarm Triggered" or "TRIGGERED".
            if "trigger" in alarm_status.lower():
                alarm_timestamps.append(timestamp)
                alarm_values.append(ldr_value)

    if len(timestamps) == 0:
        raise ValueError("The CSV file does not contain any valid data rows.")

    return timestamps, ldr_values, alarm_timestamps, alarm_values


def create_plot(
    timestamps,
    ldr_values,
    alarm_timestamps,
    alarm_values,
    csv_file_path,
):
    """
    Create, save, and display the LDR data plot.
    """
    plt.figure(figsize=(11, 6))

    # Main LDR sensor data line.
    plt.plot(
        timestamps,
        ldr_values,
        color="royalblue",
        linewidth=1.8,
        marker="o",
        markersize=3,
        label="LDR value",
    )

    # ESP32 alarm threshold.
    plt.axhline(
        y=ALARM_THRESHOLD,
        color="orange",
        linestyle="--",
        linewidth=1.5,
        label=f"Alarm threshold ({ALARM_THRESHOLD})",
    )

    # Highlight rows where the alarm was triggered.
    if alarm_timestamps:
        plt.scatter(
            alarm_timestamps,
            alarm_values,
            color="red",
            s=45,
            zorder=3,
            label="Alarm triggered",
        )

    plt.title("ESP32 Light Sensor Data")
    plt.xlabel("Time")
    plt.ylabel("LDR ADC value")
    plt.grid(True, linestyle=":", alpha=0.6)
    plt.legend()
    plt.xticks(rotation=30)
    plt.tight_layout()

    DATA_FOLDER.mkdir(exist_ok=True)
    plt.savefig(OUTPUT_IMAGE_FILE, dpi=200)

    print(f"Data loaded from: {csv_file_path}")
    print(f"Valid data rows: {len(ldr_values)}")
    print(f"Alarm-triggered rows: {len(alarm_values)}")
    print(f"Plot saved to: {OUTPUT_IMAGE_FILE}")

    plt.show()


def main():
    try:
        csv_file_path = choose_csv_file()

        (
            timestamps,
            ldr_values,
            alarm_timestamps,
            alarm_values,
        ) = load_csv_data(csv_file_path)

        create_plot(
            timestamps,
            ldr_values,
            alarm_timestamps,
            alarm_values,
            csv_file_path,
        )

    except (FileNotFoundError, ValueError) as error:
        print(f"Unable to create plot: {error}")


if __name__ == "__main__":
    main()