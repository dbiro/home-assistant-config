# My ESPHome devices

## Panasonic ACs
My external component implementation: [dbiro/esphome-panasonic-ac](https://github.com/dbiro/esphome-panasonic-ac).

## Main Indicator (control) Panel
Seed Studio's [SenseCAP Indicator D1](https://www.seeedstudio.com/SenseCAP-Indicator-D1-p-5643.html) (without internal sensors) running my custom [LVGL](https://esphome.io/components/lvgl) firmware.

### Features:
- Run [LCD anti-burn-in exercise](https://esphome.io/cookbook/lvgl#prevent-burn-in-of-lcd) when display is idle
- Multi-page structure: one overview page with control specific sub pages
- Display technical information on page header:
    - Current time in 24h format synchronized from Home Assistant
    - Title of active page
    - Indicator icon for active WiFi and Home Assistant API connection
- Control and display the state of:
    - Gas boiler thermostat
- Automatically turn on display when one or more device signals *active* state.
    - Gas boiler is heating.

## Garage door and sliding gate openings
Sensor values are provided by a Pico W1 microcontroller.

## Debug and development
- **host.yaml**: host component for developing new features
- **livingroom-control-panel.yaml**: [Guiton-ESP32-S3](https://devices.esphome.io/devices/Guition-ESP32-S3-4848S040) touchscreen based playground