# Wiring and Calibration

## Pin map

| Arduino pin | Connected component | Purpose |
|---|---|---|
| D2 | HC-SR04 TRIG | Sends the ultrasonic trigger pulse |
| D4 | HC-SR04 ECHO | Measures the returned pulse duration |
| A0 | Rain Sensor Module AO | Reads the analog rain/moisture value |
| D3 | Gate SG90 signal | Opens and closes the parking gate |
| D5 | Roof SG90 signal | Opens and closes the protective roof |

## Calibrated values

| Parameter | Value | Meaning |
|---|---:|---|
| Gate closed angle | 10° | Physical closed position |
| Gate open angle | 100° | Physical open position |
| Roof open angle | 120° | Dry-weather position |
| Roof closed angle | 0° | Rain-protection position |
| Gate detection range | Less than 20 cm | Opens the model gate |
| Gate open duration | 5 seconds | Time allowed for passage |
| Rain threshold | Below 900 | Treated as wet |

## Components

- Arduino Uno
- 2 × SG90 micro servo motors
- HC-SR04 ultrasonic distance sensor
- Rain Sensor Module with analog output
- Breadboard
- Jumper wires
- Power connections
- Physical model of the roof and parking gate

## Power note

Two servo motors can create current spikes that cause voltage drops or Arduino resets. For a more robust version, power the servos from an appropriately rated regulated 5 V supply and connect the supply ground to the Arduino ground.

Detaching a servo stops its control pulses and can reduce stationary jitter, but it does not physically disconnect the servo's power supply.

