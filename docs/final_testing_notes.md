# Final Testing Notes

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