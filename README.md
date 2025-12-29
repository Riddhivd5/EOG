# Blink controlled device
An open-source, low-cost prototype circuit that detects eye blinks to control IoT devices hands-free. 

## Features
1. Dual-Input Control - supports both bio-potential (blink) and manual (push-button) inputs with a priority-based logic system.
2. Active Noise Cancellation to reject 50Hz mains hum and RF interference.
3. Use it to control smart devices, play games, detect drowsiness.

## Hardware
| Component                     | Description                               |
| ----------------------------- | ----------------------------------------- |
| **Microcontroller**           | ESP32 (DOIT DevKit V1)                    |
| **Instrumentation Amplifier** | AD620                                     |
| **Op-Amp**                    | LM324N (optional)     |
| **Electrodes**                | Standard Ag/AgCl wet ECG/EOG electrodes   |
| **Feedback**                  | LED (visual), Buzzer (audio)              |
| **Communication**             | Bluetooth Low Energy (BLE) – HID Keyboard |
