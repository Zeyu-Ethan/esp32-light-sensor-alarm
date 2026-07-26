# Development Log

## Day 1 - Project Setup and ESP32 Bring-up

**Date:** 25/07/2026

### Objective

Set up the development environment for the ESP32 Light Sensor Alarm System and understand the basic workflow between Arduino IDE, ESP32, and Serial Monitor.

### Work Completed

- Installed Arduino IDE 2.3.10 on Windows 11.
- Installed the ESP32 board package by Espressif Systems.
- Connected the MakePico ESP32 to the laptop using a USB cable.
- Confirmed that Windows detected the ESP32 on COM5.
- Selected `ESP32 Dev Module` as the board in Arduino IDE.
- Tested basic Serial Monitor output.
- Studied the Arduino program structure, including `setup()` and `loop()`.

### Learning Point 1 - Arduino program structure

**Question:**  
Arduino programs use `setup()` and `loop()` instead of a visible `main()` function, which was different from the standard C structure I had learned before.

**Explanation:**  
`setup()` runs once after reset or power-up. After that, `loop()` runs repeatedly while the ESP32 is powered. The Arduino framework hides the lower-level `main()` function.

**Test / Result:**  
A test program printed messages in both `setup()` and `loop()`. The messages inside `setup()` appeared once, while the message inside `loop()` repeated continuously.

### Learning Point 2 - Serial communication and baud rate

**Question:**  
I was unsure whether `Serial.begin(115200)` used a fixed value or a configurable value.

**Explanation:**  
`115200` is the baud rate for serial communication. It is not fixed, but the baud rate in the code must match the setting in Serial Monitor.

**Test / Result:**  
Serial Monitor was opened at 115200 baud, and the ESP32 output displayed correctly.

### Learning Point 3 - Restarting the ESP32 program

**Question:**  
I wanted to know how to restart the program from the beginning and make `setup()` run again.

**Explanation:**  
Pressing the Reset button, unplugging and reconnecting USB, or uploading a new program can restart the ESP32.

**Test / Result:**  
After pressing the reset button, the initial messages from `setup()` appeared again, confirming that the program restarted from the beginning.

### Learning Point 4 - ESP32 execution and Serial Monitor output

**Question:**  
I was unsure whether continuous Serial Monitor output meant that the ESP32 was overloaded.

**Explanation:**  
The ESP32 continuously executes `loop()`, but Serial output only happens when the code calls `Serial.print()` or `Serial.println()`.

**Test / Result:**  
A counter test program printed values from 0 to 4 and then stopped printing. This showed that Serial output can stop while the ESP32 program continues running.

### Lessons Learned

- ESP32 code is uploaded to the microcontroller and runs on the board.
- `setup()` is used for one-time initialization.
- `loop()` is used for continuous execution.
- Serial Monitor is used to observe debugging output from the ESP32.
- Changing code in Arduino IDE does not affect the ESP32 until the new program is uploaded.
- Resetting the board restarts the program from `setup()`.

### Tasks To Do

- **Goal:** Start learning GPIO output and test controlling an LED using `pinMode()` and `digitalWrite()`.
- **Tool:** Arduino IDE and ESP32
- **Target Date:** 26/07/2026
