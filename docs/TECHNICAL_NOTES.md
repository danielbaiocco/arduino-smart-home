# Technical Notes and Limitations

## Design decisions

### Servo detach

Each servo is attached only when a movement command is issued and detached after an 800 ms movement window. This was introduced after stationary servo jitter and voltage instability were observed in the physical model.

### Gate timing

The five-second gate interval uses `millis()` instead of a five-second `delay()`. This allows the main loop to continue checking the rain subsystem during most of the gate-open period.

### Sensor timeouts

`pulseIn()` uses a 30 ms timeout. A missing echo therefore cannot block the program indefinitely.

## Accuracy notes

- The rain logic uses state-change detection around one threshold. It is not true hysteresis because the wet and dry thresholds are identical.
- The program is not fully non-blocking: servo movement uses an 800 ms delay, the main loop uses a 100 ms delay, and `pulseIn()` can block for up to 30 ms.
- If an object remains within 20 cm after the gate closes, the next loop iteration may open the gate again.
- The rain threshold and servo angles were calibrated for the original physical model and may need adjustment on other hardware.

## Possible next version

- Use separate wet and dry thresholds to implement real hysteresis.
- Replace the servo movement delay with a timed servo state.
- Average several rain-sensor samples to reduce noise.
- Add serial diagnostics for distance, rain readings, and state changes.
- Add an external regulated 5 V supply for the servos.
- Add a manual override and a safety sensor for the gate.

