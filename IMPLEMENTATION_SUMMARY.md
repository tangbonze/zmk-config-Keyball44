# Auto Mouse Timeout Implementation Summary

## Overview
This implementation adds the ability to dynamically change the auto mouse timeout at runtime by pressing keys. Three preset timeout values are configured: 1000ms, 2000ms, and 5000ms.

## What Was Changed

### 1. ZMK PMW3610 Driver (`zmk-pmw3610-driver`)

#### New Files Created:
- **`dts/bindings/zmk,behavior-auto-mouse-timeout.yaml`**
  - Device tree binding definition for the new behavior
  - Defines that the behavior takes 1 parameter (the timeout value in ms)

- **`src/behavior_auto_mouse_timeout.c`**
  - Implementation of the behavior
  - Calls `pmw3610_set_automouse_timeout_ms()` when a key is pressed
  - Logs the timeout value being set

- **`AUTO_MOUSE_TIMEOUT.md`**
  - Documentation explaining how to use the feature

#### Modified Files:
- **`CMakeLists.txt`**
  - Added `src/behavior_auto_mouse_timeout.c` to the build

### 2. Keyball44 Config (`zmk-config-Keyball44`)

#### Modified Files:
- **`config/boards/shields/keyball_nano/keyball44_right.overlay`**
  - Added behavior instance definition:
    ```dts
    behaviors {
      amt: auto_mouse_timeout {
        compatible = "zmk,behavior-auto-mouse-timeout";
        label = "AUTO_MOUSE_TIMEOUT";
        #binding-cells = <1>;
      };
    };
    ```

- **`config/keyball44.keymap`**
  - Updated MOUSE layer (layer 4) to include timeout controls
  - Mapped keys to three preset values:
    - Position 1: `&amt 1000` (1 second timeout)
    - Position 2: `&amt 2000` (2 seconds timeout)
    - Position 3: `&amt 5000` (5 seconds timeout)

## How to Use

1. **Navigate to the MOUSE layer** (layer 4)
   - This is configured as `automouse-layer = <4>` in the device tree

2. **Press one of the timeout preset keys:**
   - Press the first key (originally N1) to set timeout to 1000ms
   - Press the second key (originally N2) to set timeout to 2000ms
   - Press the third key (originally N3) to set timeout to 5000ms

3. **The timeout takes effect immediately**
   - The mouse layer will now stay active for the selected duration after you stop moving the trackball
   - The setting persists until changed or the keyboard is reset

## Example Workflow

```
1. User moves trackball → MOUSE layer activates automatically
2. User presses key 1 → Timeout set to 1000ms
3. User stops moving trackball → MOUSE layer stays active for 1 second
4. After 1 second of no movement → MOUSE layer deactivates

5. Later, user presses key 3 → Timeout set to 5000ms  
6. User stops moving trackball → MOUSE layer stays active for 5 seconds
```

## Technical Details

- The behavior uses the existing `pmw3610_set_automouse_timeout_ms()` function
- The PMW3610 device is referenced by the `trackball` label in device tree
- The implementation checks if automouse is configured before setting the timeout
- Error handling is included for device readiness and invalid parameters

## Customization

To add more timeout options or change the preset values, simply update the keymap:

```dts
&amt 500   // 0.5 seconds
&amt 1500  // 1.5 seconds
&amt 3000  // 3 seconds
```

You can use any positive integer value in milliseconds.

