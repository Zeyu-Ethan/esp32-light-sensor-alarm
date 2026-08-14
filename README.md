# ESP32 Light Sensor Alarm System

ESP32-based light sensor alarm system using an LDR sensor module, ADC input, GPIO output, buzzer alarm, DIP switch control, Serial Monitor debugging, and local Wi-Fi monitoring.

## Project Aim

The aim of this project is to build a small embedded system that detects changes in light level and triggers an alarm when the measured light value crosses a defined threshold.

The project is also extended with local Wi-Fi monitoring so that the sensor value, alarm status, switch states, and output states can be viewed from a browser on the same local network.

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

## Current Status

This project currently has a working V1 hardware alarm prototype and a V3 Wi-Fi alarm monitoring extension.

The V1 prototype reads analog values from the LDR sensor module and triggers an external LED and the ESPBlock onboard buzzer when a confirmed dark condition is detected. The alarm behaviour can be controlled using three DIP switches.

The V3 extension integrates the V1 alarm logic with a local Wi-Fi monitoring page. A browser on the same local network can view the LDR value, light condition, alarm status, switch states, LED output state, and buzzer output state.

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
- Uses a local `secrets.h` file and `.gitignore` to prevent real Wi-Fi credentials from being uploaded to GitHub.

## System Overview

The system follows an input-process-output structure.

The light sensing unit detects the environmental light level using an LDR sensor module. The ESP32 control unit reads the analog sensor value, processes the threshold logic, and decides whether the alarm condition is active. The alarm output unit provides visual and sound alerts using an external LED and the ESPBlock onboard buzzer. The user input unit allows the alarm behaviour to be configured using three DIP switches. The debugging interface is used to observe sensor readings and system status during development. In the Wi-Fi monitoring extension, the ESP32 also hosts a local web page that displays the current sensor value, alarm status, switch states, and output states.

## System Block Diagram

```mermaid
flowchart LR
    A[Light Sensing Unit] --> B[ESP32 Control Unit]
    B --> C[Alarm Output Unit]
    D[User Input Unit] --> B
    B --> E[Debugging Interface]
    B --> F[Local Web Monitoring Interface]
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
| Credential protection | Real Wi-Fi credentials stored in ignored `secrets.h` file | Passed |

*Table 4. Testing summary for the V1 hardware prototype and V3 Wi-Fi monitoring extension.*

## Project Documentation

- [Development Log](development_log.md)
- [Final Testing Notes](docs/final_testing_notes.md)

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

    section Documentation
    Development log update                         :done, 2026-08-11, 1d
    Final testing notes update                     :done, 2026-08-14, 1d
    README update and final project review         :active, 2026-08-14, 2d

    section Future Extension
    Python serial data logging and dashboard       :      2026-08-17, 7d
```
*Figure 3. Flexible development plan for the ESP32 light sensor alarm system, including V1 hardware alarm prototype, V2 sensor comparison, and V3 Wi-Fi monitoring extension.*

## Development Environment

- Arduino IDE 2.3.10
- ESP32 board package by Espressif Systems
- Board: ESP32 Dev Module
- Serial Monitor baud rate: 115200
- GitHub for version control and documentation

## Additional Experiment

An additional AO vs DO comparison test is included in `code/ao_do_comparison_test/`. This test compares the LDR module analog output `AO` with its digital comparator output `DO` to show the difference between continuous ADC readings and hardware-comparator digital signals.

## Future Improvements

Possible future improvements include:

- Improve the visual design of the local monitoring page.
- Add clearer status styling for normal, disabled, and triggered alarm states.
- Add Python-based serial data logging to record LDR values, alarm status, and switch states into CSV files.
- Add Python data analysis and real-time plotting to show how light level changes over time.
- Add an optional Python dashboard for local monitoring and analysis.
- Consider two-way control between the Python dashboard and ESP32, such as sending mute or reset commands.
- Consider using more reliable user input hardware in a future hardware revision, such as a breadboard-friendly switch module or a soldered prototyping board.
