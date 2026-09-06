# Final Testing Notes

## V1 Hardware Alarm System Tests

## Test 1 - Normal light condition

**Setup:** Alarm switch ON, LED switch ON, buzzer switch ON.  
**Input condition:** LDR exposed to room light.  
**Expected result:** LED OFF and buzzer OFF.  
**Actual result:** LED OFF and buzzer OFF.  
**Status:** Passed.

## Test 2 - Dark condition confirmed

**Setup:** Alarm switch ON, LED switch ON, buzzer switch ON.  
**Input condition:** LDR covered by hand.  
**Expected result:** After the confirmation delay, LED ON and buzzer ON.  
**Actual result:** LED ON and buzzer ON.  
**Status:** Passed.

## Test 3 - Buzzer mute switch

**Setup:** Alarm switch ON, LED switch ON, buzzer switch OFF.  
**Input condition:** LDR covered by hand.  
**Expected result:** LED ON and buzzer OFF.  
**Actual result:** LED ON and buzzer OFF.  
**Status:** Passed.

## Test 4 - LED enable switch

**Setup:** Alarm switch ON, LED switch OFF, buzzer switch ON.  
**Input condition:** LDR covered by hand.  
**Expected result:** LED OFF and buzzer ON.  
**Actual result:** LED OFF and buzzer ON.  
**Status:** Passed.

## Test 5 - Alarm enable switch

**Setup:** Alarm switch OFF.  
**Input condition:** LDR covered by hand.  
**Expected result:** LED OFF and buzzer OFF.  
**Actual result:** LED OFF and buzzer OFF.  
**Status:** Passed.

## V3 Wi-Fi Alarm Monitoring Tests

## Test 6 - Wi-Fi connection and local web access

**Setup:** ESP32 connected to a local Wi-Fi hotspot using Wi-Fi credentials stored locally.  
**Input condition:** Serial Monitor was opened after uploading the Wi-Fi web server code. A browser then opened the ESP32 local IP address from a device on the same local network.  
**Expected result:** ESP32 connects to Wi-Fi, prints its local IP address in Serial Monitor, starts the web server, and loads the web page in the browser.  
**Actual result:** ESP32 connected to Wi-Fi, printed its local IP address, started the web server, and the web page opened successfully from a browser on the same local network.  
**Status:** Passed.

## Test 7 - LDR value display on local web page

**Setup:** ESP32 running the Wi-Fi monitoring code with the LDR module connected to `GPIO34`.  
**Input condition:** Browser opened the ESP32 local web page using the local IP address.  
**Expected result:** Web page displays the LDR analog value from the ESP32.  
**Actual result:** Web page displayed the LDR analog value on the local monitoring page.  
**Status:** Passed.

## Test 8 - Credential protection check

**Setup:** Real Wi-Fi credentials moved from the main `.ino` file into a local `secrets.h` file. The `secrets.h` file was added to `.gitignore`, and a placeholder `secrets_example.h` file was added for GitHub.  
**Input condition:** Git status was checked after creating `secrets.h`, `secrets_example.h`, and `.gitignore`.  
**Expected result:** Real Wi-Fi credentials should remain local and should not be tracked by Git. GitHub should only include the placeholder example file.  
**Actual result:** `secrets.h` was ignored by Git and did not appear as an untracked file. `secrets_example.h` was available for upload with placeholder Wi-Fi values.  
**Status:** Passed.

## Test 9 - Integrated Wi-Fi alarm monitoring

**Setup:** ESP32 running the integrated Wi-Fi alarm monitoring code with the LDR module, external LED, ESPBlock onboard buzzer, alarm switch, LED switch, and buzzer switch connected.  
**Input condition:** The local monitoring page was opened while the hardware alarm system was tested under different switch states and light conditions.  
**Expected result:** Hardware alarm outputs and web page status should match. When the alarm is triggered, the LED and buzzer should respond according to their switch states, and the web page should show the correct alarm status and output states.  
**Actual result:** The integrated system was demonstrated successfully. The web page displayed the LDR value, light condition, alarm status, switch states, LED output state, and buzzer output state while the hardware system operated. The demonstration showed alarm triggered, buzzer muted, LED disabled, and alarm disabled states being reflected on the monitoring page.  
**Status:** Passed.

## Test 10 - Wi-Fi connection timeout handling

**Setup:** ESP32 running the V3 Wi-Fi alarm monitoring code with Wi-Fi connection timeout handling added.

**Input condition:** The ESP32 was started while the Wi-Fi hotspot or router was unavailable, or while the Wi-Fi connection could not be completed.

**Expected result:** The ESP32 should stop waiting for Wi-Fi after the timeout period, print a Wi-Fi connection failure message in Serial Monitor, and continue running the hardware alarm system without local web monitoring.

**Actual result:** The ESP32 reported that the Wi-Fi connection failed after the timeout period. The hardware alarm system and Serial `DATA` output continued running without the web monitoring page.

**Status:** Passed.

## V4 Python Data Extension Tests

## Test 11 - Python serial reader

**Setup:** ESP32 connected to the computer through USB Serial. Python script running in VS Code with `pyserial` installed.

**Input condition:** The ESP32 was running the Wi-Fi alarm monitoring code and sending structured `DATA` lines through Serial.

**Expected result:** Python should connect to the ESP32 through the correct COM port at `115200` baud and read Serial data successfully.

**Actual result:** Python connected to the ESP32 through `COM5` at `115200` baud and displayed structured ESP32 `DATA` output in the terminal.

**Status:** Passed.

## Test 12 - DATA line parsing

**Setup:** Python serial reader updated to filter and process only lines beginning with `DATA,`.

**Input condition:** ESP32 sent structured Serial lines containing LDR value, light condition, alarm status, switch states, and output states.

**Expected result:** Python should ignore non-data startup messages and split each valid `DATA` line into separate values.

**Actual result:** Python ignored non-data Serial messages and parsed valid `DATA` lines into individual fields, including LDR value, light condition, alarm status, switch states, LED output state, and buzzer output state.

**Status:** Passed.

## Test 13 - CSV data logging

**Setup:** Python serial data logger running with CSV logging enabled.

**Input condition:** ESP32 sent structured `DATA` lines while the alarm system was tested under normal, disabled, and triggered states.

**Expected result:** Python should add a timestamp to each valid data row and save the parsed values into a CSV file.

**Actual result:** Python saved timestamped ESP32 data into `data/serial_log.csv`. The CSV data included normal light readings, alarm disabled states, and alarm triggered states.

Example CSV row:

    2026-08-21 21:06:34,2694,Dark,Alarm Triggered,ON,ON,ON,ON,ON

**Status:** Passed.

## Test 14 - CSV data visualisation

**Setup:** Python plotting script using recorded CSV data.

**Input condition:** Recorded CSV data from the ESP32 serial data logger was used as the input file.

**Expected result:** Python should generate a plot showing recorded LDR values over time.

**Actual result:** Python generated `data/serial_log_plot.png`, showing LDR ADC values over time, the alarm threshold, and triggered alarm points.

**Status:** Passed.