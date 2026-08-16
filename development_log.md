# Development Log

## Development Period 1 - V1 Hardware Alarm Prototype

### Logbook Entry 1.1 - Project Setup and ESP32 Bring-up

**Date:** 25/07/2026

#### Objective

Set up the development environment for the ESP32 Light Sensor Alarm System and understand the basic workflow between Arduino IDE, ESP32, and Serial Monitor.

#### Work Completed

- Installed Arduino IDE 2.3.10 on Windows 11.
- Installed the ESP32 board package by Espressif Systems.
- Connected the MakePico ESP32 to the laptop using a USB cable.
- Confirmed that Windows detected the ESP32 on COM5.
- Selected `ESP32 Dev Module` as the board in Arduino IDE.
- Tested basic Serial Monitor output.
- Studied the Arduino program structure, including `setup()` and `loop()`.

#### Learning Point 1 - Arduino program structure

**Question:**  
Arduino programs use `setup()` and `loop()` instead of a visible `main()` function, which was different from the standard C structure I had learned before.

**Explanation:**  
`setup()` runs once after reset or power-up. After that, `loop()` runs repeatedly while the ESP32 is powered. The Arduino framework hides the lower-level `main()` function.

**Test / Result:**  
A test program printed messages in both `setup()` and `loop()`. The messages inside `setup()` appeared once, while the message inside `loop()` repeated continuously.

#### Learning Point 2 - Serial communication and baud rate

**Question:**  
I was unsure whether `Serial.begin(115200)` used a fixed value or a configurable value.

**Explanation:**  
`115200` is the baud rate for serial communication. It is not fixed, but the baud rate in the code must match the setting in Serial Monitor.

**Test / Result:**  
Serial Monitor was opened at 115200 baud, and the ESP32 output displayed correctly.

#### Learning Point 3 - Restarting the ESP32 program

**Question:**  
I wanted to know how to restart the program from the beginning and make `setup()` run again.

**Explanation:**  
Pressing the Reset button, unplugging and reconnecting USB, or uploading a new program can restart the ESP32.

**Test / Result:**  
After pressing the reset button, the initial messages from `setup()` appeared again, confirming that the program restarted from the beginning.

#### Learning Point 4 - ESP32 execution and Serial Monitor output

**Question:**  
I was unsure whether continuous Serial Monitor output meant that the ESP32 was overloaded.

**Explanation:**  
The ESP32 continuously executes `loop()`, but Serial output only happens when the code calls `Serial.print()` or `Serial.println()`.

**Test / Result:**  
A counter test program printed values from 0 to 4 and then stopped printing. This showed that Serial output can stop while the ESP32 program continues running.

#### Lessons Learned

- ESP32 code is uploaded to the microcontroller and runs on the board.
- `setup()` is used for one-time initialization.
- `loop()` is used for continuous execution.
- Serial Monitor is used to observe debugging output from the ESP32.
- Changing code in Arduino IDE does not affect the ESP32 until the new program is uploaded.
- Resetting the board restarts the program from `setup()`.

#### Tasks To Do

- **Goal:** Start learning GPIO output and test controlling an LED using `pinMode()` and `digitalWrite()`.
- **Tool:** Arduino IDE and ESP32
- **Target Date:** 26/07/2026

### Logbook Entry 1.2 - GPIO Output and LED Blink Test

**Date:** 26/07/2026

#### Objective

Start learning GPIO output and test controlling an LED using `pinMode()` and `digitalWrite()`.

#### Work Completed

- Connected an external LED to ESP32 `GPIO25` through a current-limiting resistor.
- Set `GPIO25` as an output using `pinMode()`.
- Used `digitalWrite()` to switch the LED on and off.
- Used Serial Monitor to print `LED ON` and `LED OFF` messages.
- Tested the reset button after uploading the program.

#### Test / Result

- The program uploaded successfully to the ESP32.
- The LED blinked at approximately 1-second intervals.
- Serial Monitor output matched the expected LED states.
- Pressing the reset button restarted the program successfully.

#### Issue 1 - Compilation error caused by incorrect constant name

**Problem:**  
The program failed to compile with the error `'High' was not declared in this scope`.

**Cause:**  
Arduino constants are case-sensitive. I wrote `High` instead of `HIGH`.

**Solution:**  
Changed `High` to `HIGH` in `digitalWrite(ledPin, HIGH);`.

**Test / Result:**  
After correcting the constant name, the program uploaded successfully.

#### Issue 2 - Incorrect use of the power rail during LED wiring

**Problem:**  
During the first wiring attempt, the `3.3V` pin was connected to the breadboard `+` power rail, and `GPIO25` was also connected to the same `+` rail.

**Cause:**  
This connection did not match the purpose of the GPIO output test. The aim was to use `GPIO25` as a controllable output signal to switch the LED on and off, not to connect the LED directly to a fixed `3.3V` supply.

**Safety Check:**  
Before powering the circuit, the wiring was checked again. This helped identify that `GPIO25` and the fixed `3.3V` supply should not be connected to the same power rail for this test.

**Solution:**  
The `3.3V` wire was removed from the `+` rail. The circuit was changed so that `GPIO25` was used as the controllable output source through a current-limiting resistor and LED to GND.

**Corrected Circuit:**  
`GPIO25 → resistor → LED → GND`

**Test / Result:**  
After correcting the wiring and uploading the program, the LED blinked at approximately 1-second intervals. The Serial Monitor output matched the LED state, showing `LED ON` and `LED OFF`.

#### Lessons Learned

- GPIO pins can be configured as outputs using `pinMode()`.
- `digitalWrite()` can set a GPIO output to `HIGH` or `LOW`.
- `HIGH` and `LOW` must be written in uppercase.
- ESP32 outputs approximately 3.3V when a GPIO pin is set to `HIGH`.
- Serial Monitor can be used to confirm program behaviour while observing hardware output.
- Verify can check code syntax before uploading to the ESP32.
- Circuit wiring should be checked before powering the board to reduce the risk of short circuits or incorrect connections.

#### Tasks To Do

- **Goal:** Read analog values from the LDR sensor module using `analogRead()`.
- **Tool:** Arduino IDE, ESP32, LDR sensor module
- **Target Date:** 27/07/2026

### Logbook Entry 1.3 - LDR Analog Input and Threshold LED Control

**Date:** 28/07/2026

#### Schedule Note

The LDR analog input test was originally planned for 27/07/2026, but it was moved to 28/07/2026 due to limited available time.

#### Objective

Test the LDR sensor module using ESP32 analog input and use the measured values to control an LED with a threshold.

#### Work Completed

- Tested the LDR sensor module using analog input on `GPIO34`.
- Recorded ADC value ranges under bedroom light, covered condition, and phone flashlight.
- Selected an initial threshold value of `1200` based on the measured sensor values.
- Implemented threshold-based LED control using `GPIO25`.

#### Test / Result

| Condition | ADC Value Range | System Result |
|---|---:|---|
| Bedroom light | 656-755 | LED OFF |
| Covered by hand | 1680-2651 | LED ON |
| Phone flashlight | 272-292 | LED OFF |

The test showed that the ADC value increased when the LDR sensor was covered and decreased when the sensor was exposed to stronger light. With the threshold set to `1200`, the LED turned on in dark conditions and turned off in brighter conditions.

#### Lessons Learned

- The ESP32 ADC reads voltage, not resistance directly.
- Although an LDR has lower resistance under stronger light, the ADC value depends on the sensor module's internal voltage divider circuit.
- In this module setup, stronger light produced a lower ADC value and darker conditions produced a higher ADC value.
- Sensor values should be measured before choosing a threshold.
- `const` can be used for fixed configuration values such as pin numbers and threshold values.
- `Serial.print()` can be used with `Serial.println()` to display a label, value, and status on the same line.

#### Tasks To Do

- **Goal:** Add buzzer output to provide an audible alarm when the dark condition is detected.
- **Tool:** Arduino IDE, ESP32, LDR sensor module, LED, buzzer
- **Target Date:** 29/07/2026

### Logbook Entry 1.4 - Buzzer Output and Alarm Integration

**Date:** 29/07/2026

#### Objective

Test the ESPBlock onboard buzzer as an output device and integrate it with the LDR threshold alarm logic.

#### Work Completed

- Tested the ESPBlock onboard buzzer using `GPIO27`.
- Confirmed that the onboard buzzer can be controlled by ESP32 digital output.
- Integrated the buzzer with the existing LDR threshold and LED control logic.
- Updated the alarm logic so that dark conditions trigger both visual and audible alerts.

#### Test / Result

| Condition | Expected Result | Actual Result |
|---|---|---|
| Normal room light | LED OFF, buzzer OFF | Passed |
| LDR covered by hand | LED ON, buzzer ON | Passed |
| LDR exposed to stronger light | LED OFF, buzzer OFF | Passed |

The test confirmed that the LDR threshold can control both the LED and ESPBlock onboard buzzer. When the LDR value was above the threshold, the LED turned on and the buzzer sounded. When the LDR value was below the threshold, both outputs turned off.

#### Issues / Fixes

##### Issue 1 - Buzzer briefly turned on during startup

**Problem:**  
The intended startup state was LED off and buzzer off. However, after uploading the first version of the integrated code, the buzzer briefly turned on during startup.

**Cause:**  
The ESPBlock onboard buzzer is active-low, so `LOW` turns it on and `HIGH` turns it off. In the first version of the code, the buzzer was set to `HIGH` after the startup delay, which allowed it to briefly turn on before reaching the intended off state.

**Fix:**  
The buzzer was set to the off state earlier in `setup()` by moving `digitalWrite(buzzerPin, HIGH);` before the startup delay.

**Result:**  
After uploading the revised code, the buzzer stayed off during initialization as intended.

#### Lessons Learned

- The ESPBlock onboard buzzer can be controlled using `GPIO27`.
- The ESPBlock onboard buzzer is active-low, so `LOW` turns it on and `HIGH` turns it off.
- Output devices should be set to their intended initial states before startup delays to reduce unwanted behaviour during initialization.

#### Future Improvement

- Refine the threshold value because the current value of `1200` is too sensitive and can be triggered by weak shadows.

#### Tasks To Do

- **Goal:** Refine the alarm threshold and improve the alarm behaviour to reduce false triggering.
- **Tool:** Arduino IDE, ESP32, LDR sensor module, LED, ESPBlock onboard buzzer
- **Target Date:** 30/07/2026

### Logbook Entry 1.5 - Threshold Refinement and Alarm Control Switches

**Date:** 30/07/2026

#### Objective

Refine the alarm trigger behaviour and add configurable switch controls for the light sensor alarm system.

#### Work Completed

- Tested additional LDR readings under different lighting and shadow conditions.
- Updated the alarm threshold from `1200` to `2000` to reduce unwanted triggering from weak shadows.
- Added a `1000 ms` confirmation delay before activating the alarm output.
- Added DIP switch 1 as an alarm enable switch using `GPIO26`.
- Added DIP switch 2 as a buzzer mute switch using `GPIO32`.
- Added DIP switch 3 as an LED enable switch using `GPIO33`.
- Integrated the three switch inputs with the existing LDR, LED, and buzzer alarm logic.

#### Test / Result

##### Threshold Refinement Test

| Condition | ADC Value Range | Result with Threshold `2000` |
|---|---:|---|
| Bedroom light | 732-855 | Alarm not triggered |
| Weak shadow | 1571-1847 | Alarm not triggered |
| LDR covered by hand | 2323-2939 | Alarm triggered |
| Room light off | 3933-4047 | Alarm triggered |

The threshold was updated to `2000` because it separated weak shadows from stronger dark conditions more reliably. A `1000 ms` confirmation delay was added so that the alarm only triggers when the dark condition remains present.

##### Switch Control Test

| Test | Switch State | LDR Condition | Expected Result | Actual Result |
|---|---|---|---|---|
| Alarm disabled | Switch 1 OFF | Covered / dark | LED OFF, buzzer OFF | Passed |
| Alarm enabled | Switch 1 ON | Covered / dark | Alarm logic active | Passed |
| Buzzer muted | Switch 1 ON, Switch 2 OFF | Covered / dark | LED ON, buzzer OFF | Passed |
| Buzzer enabled | Switch 1 ON, Switch 2 ON | Covered / dark | LED ON, buzzer ON | Passed |
| LED disabled | Switch 1 ON, Switch 3 OFF | Covered / dark | LED OFF, buzzer controlled by Switch 2 | Passed |
| LED enabled | Switch 1 ON, Switch 3 ON | Covered / dark | LED ON when dark is confirmed | Passed |

The test confirmed that the alarm system can now be configured using three independent switch inputs. Switch 1 controls whether the alarm system is enabled, Switch 2 controls whether the buzzer is allowed to sound, and Switch 3 controls whether the LED is allowed to turn on.

#### Issues / Fixes

##### Issue 1 - Alarm was too sensitive to weak shadows

**Problem:**  
The previous threshold value made the alarm too sensitive. Weak shadows over the LDR could trigger the LED and buzzer.

**Cause:**  
The threshold value was too low for the measured lighting conditions. A single ADC reading above the threshold could also trigger the alarm immediately, even if the dark condition was only temporary.

**Fix:**  
Additional ADC readings were recorded under bedroom light, weak shadow, hand-covered, and room-light-off conditions. The threshold was increased to `2000`, and a `1000 ms` confirmation delay was added before activating the alarm.

**Result:**  
Weak shadows no longer triggered the alarm, while stronger dark conditions such as covering the LDR or turning off the room light still triggered the alarm successfully.

##### Issue 2 - Blocking switch-control structure was not suitable for the main loop

**Problem:**  
A `while` loop was considered for handling switch-controlled alarm states, but this structure was not suitable for the current system.

**Cause:**  
A `while` loop can block the main program flow if it remains inside one condition. This would make the system less suitable for continuously checking multiple inputs, including the alarm enable switch, buzzer mute switch, LED enable switch, and LDR sensor value.

**Fix:**  
The switch logic was implemented using `if` conditions inside `loop()`. The alarm enable switch uses an early `return` when the system is disabled, allowing the program to skip the alarm logic for that loop cycle and then check the switch state again in the next cycle.

**Result:**  
The program can continuously check the LDR and all switch inputs without being locked inside a blocking loop structure.

#### Lessons Learned

- A suitable pull-down resistor, such as `10kΩ`, should be used for DIP switch input circuits instead of a low-value resistor used for LED current limiting.
- Each independent switch function needs its own GPIO input.
- Using an early `return` is useful when a disabled state should skip the remaining alarm logic in the current `loop()` cycle.

#### Future Improvement

- Optimise Serial Monitor output after the main switch functions are completed.

#### Tasks To Do

- **Goal:** Review and clean up the project code, then start improving the README and project documentation.
- **Tool:** Arduino IDE, ESP32, LDR sensor module, LED, ESPBlock onboard buzzer, DIP switch
- **Target Date:** 31/07/2026

## Development Period 2 - V2 Sensor Output Comparison

**Date:** 02/08/2026

#### Objective

Compare the LDR sensor module analog output `AO` with its digital comparator output `DO`.

#### Work Completed

- Connected the LDR module `AO` output to ESP32 `GPIO34`.
- Connected the LDR module `DO` output to ESP32 `GPIO35`.
- Wrote a separate AO vs DO comparison test program.
- Used `analogRead()` to read the continuous AO value.
- Used `digitalRead()` to read the DO state.
- Observed how the DO state changed when the light level changed.

#### Test / Result

The AO value changed continuously as the light level changed, while the DO output only changed between `LOW` and `HIGH`.

Example Serial Monitor output:

    LDR AO value: 1840 | LDR DO state: LOW
    LDR AO value: 1920 | LDR DO state: HIGH
    LDR AO value: 2672 | LDR DO state: HIGH

The test showed that the DO output changed state when the AO value was approximately between `1840` and `1920`.

#### Lessons Learned

- `AO` provides a continuous analog signal that can be read using the ESP32 ADC.
- `DO` provides a digital `HIGH` or `LOW` signal from the LDR module's onboard comparator.
- The ESP32 software threshold used in the V1 alarm code does not control the LDR module's `DO` output.
- The `DO` switching point is controlled by the LDR module hardware comparator threshold.

#### Tasks To Do

- **Goal:** Start the Wi-Fi monitoring extension and test whether the ESP32 can connect to a local Wi-Fi network.
- **Tool:** Arduino IDE, ESP32, LDR sensor module, Serial Monitor
- **Target Date:** 03/08/2026

## Development Period 3 - V3 Local Wi-Fi Alarm Monitoring

**Date:** 03/08/2026 - 09/08/2026

#### Objective

Extend the ESP32 light sensor alarm system with local Wi-Fi monitoring, allowing the alarm system status to be viewed from a browser on the same local network.

#### Work Completed

- Added ESP32 Wi-Fi support using the built-in Wi-Fi capability.
- Tested Wi-Fi connection using a local hotspot and confirmed that the ESP32 could obtain a local IP address.
- Added a local web server using the ESP32 `WebServer` library.
- Created a browser-accessible test page to confirm that the ESP32 could respond to HTTP requests.
- Updated the Wi-Fi monitoring page to display alarm status, switch states, LED output state, buzzer output state, and automatic page refresh.
- Integrated the V1 alarm logic with the Wi-Fi monitoring code.
- Restructured the V1 alarm logic to run alongside the web server.
- Replaced blocking `delay()` confirmation timing with non-blocking `millis()` timing.
- Added a local `secrets.h` file for real Wi-Fi credentials.
- Added `secrets.h` to `.gitignore` so that local Wi-Fi credentials are not uploaded to GitHub.
- Added `secrets_example.h` to show the required credential format using placeholder values.

#### Test / Result

The Wi-Fi connection test confirmed that the ESP32 could connect to a local hotspot and print its local IP address in Serial Monitor.

Example Serial Monitor output:

    Wi-Fi connected successfully
    IP address: 172.20.10.10
    Web server started

The basic web server test confirmed that the ESP32 could host a local web page and respond to browser requests from a device on the same local network.

The final integrated test confirmed that the ESP32 could run the hardware alarm system and provide local web monitoring at the same time. The web page displayed the current alarm status, switch states, LED output state, and buzzer output state while the hardware alarm logic continued to operate independently.

#### Issues / Fixes

##### Issue 1 - Upload failed when flashing the larger Wi-Fi web server code

**Problem:**  
The Wi-Fi web server code compiled successfully, but uploading to the ESP32 failed with a flash connection error.

**Cause:**  
The program size increased after adding Wi-Fi and web server functionality. The higher upload speed was less reliable for the current USB connection.

**Fix:**  
The Arduino IDE upload speed was reduced to a more stable value.

**Result:**  
The code uploaded successfully after reducing the upload speed.

##### Issue 2 - Hard-coded Wi-Fi credential structure could lead to accidental password exposure

**Problem:**  
The first Wi-Fi code structure placed `ssid` and `password` values directly inside the main `.ino` file. Even when placeholder values are used, this structure can make it easy for users to accidentally replace them with real credentials during local testing and then upload the file to GitHub.

**Cause:**  
The main `.ino` file is part of the public project code. If real Wi-Fi credentials are typed into this file for testing, they may be accidentally committed.

**Fix:**  
The project was updated to use a separate local `secrets.h` file for real Wi-Fi credentials. This file is ignored by Git using `.gitignore`. A `secrets_example.h` file was added to show the required format using placeholder values.

**Result:**  
The Wi-Fi configuration is now safer and more user-friendly. Real credentials stay local, while the GitHub repository still provides an example file for other users.

##### Issue 3 - The V1 blocking delay structure was not suitable for Wi-Fi monitoring

**Problem:**  
The original V1 alarm logic used `delay()` for dark-condition confirmation. This was acceptable for the standalone alarm prototype, but less suitable for the Wi-Fi monitoring version.

**Cause:**  
A blocking delay stops the main program flow temporarily. In the Wi-Fi version, the main loop also needs to call `server.handleClient()` regularly so that browser requests can be processed.

**Fix:**  
The dark-condition confirmation logic was changed to use `millis()` timing. The code records when the dark condition first appears and only triggers the alarm if the condition remains present for the required confirmation time.

**Result:**  
The alarm system can still reduce false triggers from short shadows while keeping the local web server responsive.

##### Issue 4 - Web monitoring needed to be separated from alarm control

**Problem:**  
The earlier web monitoring test read the LDR value directly inside the web page handler. This was suitable for a simple sensor display test, but not for the final alarm monitoring system.

**Cause:**  
If sensor reading and alarm control are placed only inside the web page handler, the alarm system behaviour could become dependent on browser access. The alarm should continue running even when no browser is connected.

**Fix:**  
The code was restructured so that `updateAlarmSystem()` handles sensor reading, switch input, alarm decisions, and output control. The web page handler only displays the latest stored system state.

**Result:**  
The alarm system runs independently from browser access, while the web page acts as a monitoring interface.

#### Lessons Learned

- A local ESP32 web server is only accessible from devices on the same local network.
- The IP address printed in Serial Monitor is a local network address, not a public internet address.
- Upload speed and Serial Monitor baud rate are separate settings.
- Larger ESP32 programs may need a lower upload speed for reliable flashing.
- A local `secrets.h` file and `.gitignore` provide a safer structure for Wi-Fi projects.
- A working standalone embedded system may need to be restructured before it is integrated with Wi-Fi or web server functionality.
- Blocking `delay()` timing should be avoided when the program also needs to handle web server requests.
- `millis()` timing allows the alarm system and web server to run together without blocking the main loop.
- Separating alarm control logic from web page generation makes the program easier to test and extend.

#### Future Improvement

- Improve the visual design of the monitoring page.
- Add clearer status styling for normal, disabled, and triggered alarm states.
- Consider adding light-level data logging in a future version.
- Consider reorganising the code folders using clearer V1, V2, and V3 naming.

#### Tasks To Do

- **Goal:** Update the README and project documentation to describe the Wi-Fi alarm monitoring extension.
- **Tool:** GitHub, README, development log, Arduino IDE, ESP32 prototype
- **Target Date:** 12/08/2026

## Development Period 4 - V4 Python Serial Data Reader

### Logbook Entry 4.1 - Basic Python Serial Reader

**Date:** 16/08/2026

#### Work Completed

- Added structured `DATA` output to the ESP32 V3 Wi-Fi monitoring code.
- Created `serial_data_logger.py` as the first Python script for reading ESP32 Serial data.
- Installed and used the `pyserial` package for Python serial communication.
- Confirmed that Python could connect to the ESP32 through `COM5` at `115200` baud.
- Confirmed that Python could read structured `DATA` lines from the ESP32.

#### Test / Result

The Python serial reader successfully connected to the ESP32 and displayed structured Serial data in the VS Code terminal.

Example output:

    DATA,816,Light,Alarm Disabled,OFF,OFF,MUTED,OFF,OFF
    DATA,813,Light,Alarm Disabled,OFF,OFF,MUTED,OFF,OFF

This confirmed that the ESP32 could send structured status data through USB Serial and that Python could read it.

#### Lessons Learned

- `pyserial` allows Python to communicate with the ESP32 through a serial COM port.
- The Python baud rate must match `Serial.begin(115200)` in the ESP32 code.
- Arduino Serial Monitor and Python should not use the same COM port at the same time.
- A structured `DATA,...` format is easier for Python to process than normal human-readable debug messages.
- Python can be added as a PC-side extension to read and process data from the ESP32.

#### Tasks To Do

- **Goal:** Update the Python script so that it only processes lines beginning with `DATA,`, splits each data line into separate values, and saves the parsed data into a CSV file with timestamps.
- **Tool:** VS Code, Python, pyserial, ESP32, USB Serial
- **Target Date:** 17/08/2026