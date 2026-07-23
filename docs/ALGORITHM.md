# Control Algorithm

## Rain-protection subsystem

1. Read the analog value from the rain sensor on A0.
2. Treat a reading below 900 as wet.
3. If the system changes from dry to wet, move the roof servo to 0°.
4. If the system changes from wet to dry, move the roof servo to 120°.
5. Do not command the servo repeatedly while the state remains unchanged.

## Parking-gate subsystem

1. Trigger the HC-SR04 sensor.
2. Convert the echo-pulse duration into distance.
3. If the distance is between 0 and 20 cm and the gate is closed, move the gate servo to 100°.
4. Record the opening time with `millis()`.
5. After five seconds, move the gate servo back to 10°.
6. If the ultrasonic reading times out, return 999 cm so the gate is not opened accidentally.

## State variables

- `isRainingState` prevents repeated roof movements while the rain state is unchanged.
- `isGateOpen` records whether the parking gate is currently open.
- `gateTimer` stores the time at which the gate was opened.

