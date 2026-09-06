# ESP32 Light Sensor Alarm System

ESP32-based light sensor alarm system using an LDR sensor module, ADC input, GPIO output, buzzer alarm, DIP switch control, Serial Monitor debugging, local Wi-Fi monitoring, and Python-based serial data logging.

## Project Aim

The aim of this project is to build a small embedded system that detects changes in light level and triggers an alarm when the measured light value crosses a defined threshold.

The project is extended with local Wi-Fi monitoring so that the sensor value, alarm status, switch states, and output states can be viewed from a browser on the same local network.

The project also includes a Python data extension that reads structured ESP32 Serial output, saves sensor and alarm status data into a CSV file, and visualises recorded LDR values from the CSV data.

This project is also used to practise core embedded systems concepts, including:

- GPIO input and output
- ADC sensor reading
- Threshold-based control logic
- LED and buzzer output
- DIP switch input control
- Serial Monitor debugging
- Basic control logic
- Local Wi-Fi monitoring
- Basic web server implementation
- Python serial communication
- CSV data logging
- Basic data visualisation from recorded sensor data

## Current Status

This project currently has a working V1 hardware alarm prototype, a V3 local Wi-Fi alarm monitoring extension, and a V4 Python data extension.

The V1 prototype reads analog values from the LDR sensor module and triggers an external LED and the ESPBlock onboard buzzer when a confirmed dark condition is detected. The alarm behaviour can be controlled using three DIP switches.

The V3 extension integrates the V1 alarm logic with a local Wi-Fi monitoring page. A browser on the same local network can view the LDR value, light condition, alarm status, switch states, LED output state, and buzzer output state. Wi-Fi connection timeout handling was also added so that the hardware alarm system can continue running even if Wi-Fi monitoring is unavailable.

The V4 Python data extension reads structured `DATA` lines from the ESP32 through USB Serial, parses the values, saves the data into a CSV file with timestamps, and generates a plot of recorded LDR values.

## Implemented Features

- Reads analog light level from an LDR sensor module using ESP32 ADC.
- Uses a threshold value to detect dark conditions.
- Uses confirmation timing to reduce false triggering from short shadows.
- Controls an external LED as a visual alarm output.
- Controls the ESPBlock onboard buzzer as an audible alarm output.
- Uses DIP switch 1 to enable or disable the alarm system.
- Uses DIP switch 2 to enable or mute the buzzer.
- Uses DIP switch 3 to enable or disable the LED.
- Displays sensor values and system status in Serial Monitor.
- Provides local Wi-Fi monitoring using the ESP32 built-in Wi-Fi capability.
- Hosts a local web page using the ESP32 `WebServer` library.
- Displays LDR value, light condition, alarm status, switch states, LED output state, and buzzer output state on the monitoring page.
- Uses non-blocking `millis()` timing in the Wi-Fi version so that the web server can remain responsive.
- Adds Wi-Fi connection timeout handling so that the ESP32 does not wait indefinitely if Wi-Fi connection fails.
- Continues running the hardware alarm logic even when Wi-Fi monitoring is unavailable.
- Uses a local `secrets.h` file and `.gitignore` to prevent real Wi-Fi credentials from being uploaded to GitHub.
- Outputs structured `DATA` lines through Serial for Python processing.
- Uses Python and `pyserial` to read ESP32 Serial data from a COM port.
- Filters and parses structured ESP32 `DATA` lines.
- Saves LDR values, alarm status, switch states, and output states into a CSV file with timestamps.
- Provides sample CSV data for recorded system behaviour.
- Generates a basic plot of LDR values from the recorded CSV data.

## System Overview

The system follows an input-process-output structure.

The light sensing unit detects the environmental light level using an LDR sensor module. The ESP32 control unit reads the analog sensor value, processes the threshold logic, and decides whether the alarm condition is active. The alarm output unit provides visual and sound alerts using an external LED and the ESPBlock onboard buzzer. The user input unit allows the alarm behaviour to be configured using three DIP switches. The debugging interface is used to observe sensor readings and system status during development. In the Wi-Fi monitoring extension, the ESP32 also hosts a local web page that displays the current sensor value, alarm status, switch states, and output states. In the Python data extension, structured Serial data is logged to CSV and visualised for simple offline analysis.

## System Block Diagram

```mermaid
flowchart LR
    A[Light Sensing Unit] --> B[ESP32 Control Unit]
    B --> C[Alarm Output Unit]
    D[User Input Unit] --> B
    B --> E[Debugging Interface]
    B --> F[Local Web Monitoring Interface]
    B --> G[Python Data Logging Interface]
```

*Figure 1. Overview of the ESP32 light sensor alarm system.*

### Block Description

| Block | Purpose |
|---|---|
| Light Sensing Unit | Detects environmental light level using the LDR sensor module. |
| ESP32 Control Unit | Reads the sensor input, processes the threshold logic, and controls system behaviour. |
| Alarm Output Unit | Provides visual and sound alerts using an external LED and the ESPBlock onboard buzzer. |
| User Input Unit | Allows alarm enable, buzzer mute, and LED enable control using DIP switches. |
| Debugging Interface | Displays sensor values and system status during development. |
| Local Web Monitoring Interface | Displays sensor value, alarm status, switch states, and output states through a browser on the same local network. |
| Python Data Logging Interface | Reads structured ESP32 Serial output, saves data into a CSV file, and generates a plot from recorded sensor values. |

*Table 1. Block description of the ESP32 light sensor alarm system.*

## Hardware

- ESP32 development board
- ESPBlock expansion board
- LDR sensor module
- External LED
- 330Ω resistor for LED current limiting
- 10kΩ resistors for DIP switch pull-down inputs
- 4-position DIP switch
- ESPBlock onboard buzzer
- Jumper wires
- USB cable

## Hardware Prototype

![Final V1 prototype overview](media/photos/final_prototype_overview.jpg)

*Figure 2. Final V1 working prototype showing the LDR sensor module, external LED, ESPBlock onboard buzzer, and DIP switch controls.*

## Demo Videos

- [Watch the V1 hardware alarm demo](https://youtu.be/25t3WMKX8aA)
- [Watch the V3 Wi-Fi alarm monitoring demo](https://youtu.be/dECyC5ZzRzY)

## Python Data Extension

The V4 Python data extension reads structured Serial data from the ESP32 and saves the parsed values into a CSV file for later analysis.

The ESP32 outputs structured `DATA` lines in the following format:

    DATA,LDR value,Light condition,Alarm status,Alarm switch,LED switch,Buzzer switch,LED output,Buzzer output

Example ESP32 Serial output:

    DATA,2694,Dark,Alarm Triggered,ON,ON,ON,ON,ON

The Python script reads these lines through USB Serial, adds a timestamp, and saves the result into a CSV file.

Example CSV format:

    timestamp,ldr_value,light_condition,alarm_status,alarm_switch,led_switch,buzzer_switch,led_output,buzzer_output
    2026-08-21 21:06:34,2694,Dark,Alarm Triggered,ON,ON,ON,ON,ON

The recorded CSV data can then be used to generate a simple plot showing how the LDR value changes over time. The plot also shows the alarm threshold and highlights the points where the alarm was triggered.

- [Sample CSV data](data/sample_serial_log.csv)
- [LDR value plot](data/serial_log_plot.png)

![LDR value plot](data/serial_log_plot.png)

*Figure 3. Example Python-generated plot showing recorded LDR ADC values over time, alarm threshold, and triggered alarm points.*

## Pin Assignment

| Component | ESP32 Pin | Purpose |
|---|---:|---|
| LDR module `AO` | `GPIO34` | Analog light-level input |
| External LED | `GPIO25` | Visual alarm output |
| ESPBlock onboard buzzer | `GPIO27` | Audible alarm output |
| DIP switch 1 | `GPIO26` | Alarm enable control |
| DIP switch 2 | `GPIO32` | Buzzer mute control |
| DIP switch 3 | `GPIO33` | LED enable control |

*Table 2. Pin assignment for the current working prototype.*

## Wiring Reference

The wire colours below describe the hardware wiring shown in Figure 2. The V3 Wi-Fi monitoring extension uses the same core hardware connections.

| Wire Colour | Connection |
|---|---|
| Red wire | VCC / power connection |
| Black wire | GND connection |
| Brown wire | LDR module `AO` connected to `GPIO34` |
| Orange wire | External LED connected to `GPIO25` |
| Purple wire | ESPBlock onboard buzzer controlled by `GPIO27` |
| Yellow wire | DIP switch 1 connected to `GPIO26` |
| Green wire | DIP switch 2 connected to `GPIO32` |
| Blue wire | DIP switch 3 connected to `GPIO33` |

*Table 3. Wiring reference for the hardware prototype photo.*

## Testing Summary

| Test Area | Description | Status |
|---|---|---|
| GPIO output | External LED blink test using `GPIO25` | Passed |
| Analog input | LDR module `AO` reading using `GPIO34` | Passed |
| Threshold control | LED controlled by LDR threshold | Passed |
| Buzzer output | ESPBlock onboard buzzer controlled by `GPIO27` | Passed |
| Alarm integration | LDR triggers LED and buzzer together | Passed |
| False trigger reduction | Threshold refined to `2000` with confirmation delay | Passed |
| Alarm enable switch | DIP switch 1 enables or disables the system | Passed |
| Buzzer mute switch | DIP switch 2 enables or mutes buzzer output | Passed |
| LED enable switch | DIP switch 3 enables or disables LED output | Passed |
| Wi-Fi connection | ESP32 connects to local Wi-Fi and prints local IP address | Passed |
| Local web server | Browser accesses ESP32 monitoring page on the same local network | Passed |
| Web monitoring display | Page displays LDR value, alarm status, switch states, and output states | Passed |
| Wi-Fi alarm integration | Hardware alarm logic runs while local web monitoring remains active | Passed |
| Wi-Fi timeout handling | ESP32 reports Wi-Fi connection failure after a timeout and continues hardware alarm operation | Passed |
| Credential protection | Real Wi-Fi credentials stored in ignored `secrets.h` file | Passed |
| Python serial reader | Python connects to ESP32 through USB Serial and reads structured `DATA` lines | Passed |
| DATA line parsing | Python filters `DATA` lines and splits them into separate values | Passed |
| CSV data logging | Python saves parsed ESP32 data into a CSV file with timestamps | Passed |
| CSV data visualisation | Python generates a plot from recorded LDR values | Passed |

*Table 4. Testing summary for the V1 hardware prototype, V3 Wi-Fi monitoring extension, and V4 Python data extension.*

## Project Documentation

- [Development Log](development_log.md)
- [Final Testing Notes](docs/final_testing_notes.md)
- [Sample CSV data](data/sample_serial_log.csv)
- [LDR value plot](data/serial_log_plot.png)

## Development Plan

This development plan is flexible and may be adjusted depending on hardware availability, testing results, and study schedule.

```mermaid
gantt
    title ESP32 Light Sensor Alarm System - Development Plan
    dateFormat  YYYY-MM-DD

    section Setup
    Toolchain setup and board test                 :done, 2026-07-25, 1d

    section V1 Hardware Alarm Prototype
    GPIO output and LDR sensor testing             :done, 2026-07-26, 3d
    Threshold refinement and false trigger reduction :done, 2026-07-28, 2d
    Buzzer and DIP switch alarm controls           :done, 2026-07-29, 2d
    V1 prototype code cleanup and demo             :done, 2026-08-01, 1d

    section V2 Sensor Output Comparison
    AO and DO comparison test                      :done, 2026-08-02, 1d

    section V3 Wi-Fi Alarm Monitoring
    Wi-Fi web server test                          :done, 2026-08-03, 1d
    LDR value web monitoring and credential handling :done, 2026-08-07, 1d
    Integrated alarm logic with Wi-Fi monitoring   :done, 2026-08-09, 1d
    Wi-Fi connection timeout handling              :done, 2026-08-23, 1d

    section V4 Python Data Extension
    Python serial reader and DATA parsing          :done, 2026-08-16, 2d
    CSV data logging                               :done, 2026-08-18, 4d
    CSV data visualisation                         :done, 2026-08-21, 2d

    section Documentation
    Development log update                         :done, 2026-08-11, 1d
    Final testing notes update                     :done, 2026-08-14, 1d
    README update and final project review         :done, 2026-08-23, 10d
```

*Figure 4. Flexible development plan for the ESP32 light sensor alarm system, including V1 hardware alarm prototype, V2 sensor comparison, V3 Wi-Fi monitoring, and V4 Python data extension.*

## Development Environment

- Arduino IDE 2.3.10
- ESP32 board package by Espressif Systems
- Board: ESP32 Dev Module
- Serial Monitor baud rate: 115200
- Python 3.13.15
- pyserial
- matplotlib
- GitHub for version control and documentation

## Additional Experiment

An additional AO vs DO comparison test is included in `code/ao_do_comparison_test/`. This test compares the LDR module analog output `AO` with its digital comparator output `DO` to show the difference between continuous ADC readings and hardware-comparator digital signals.

## Future Improvements

Possible future improvements include:

- Improve the visual design of the local monitoring page.
- Add clearer status styling for normal, disabled, and triggered alarm states.
- Add an optional Python dashboard for local monitoring and analysis.
- Consider two-way control between the Python dashboard and ESP32, such as sending mute or reset commands.
- Add more advanced data analysis, such as alarm event counting or dark-condition duration measurement.
- Consider using more reliable user input hardware in a future hardware revision, such as a breadboard-friendly switch module or a soldered prototyping board.