# Light PID Controller

An ESP32-S3 closed-loop light controller. An LDR measures brightness, and the
firmware adjusts an LED's PWM duty to hold the reading at a target setpoint.

**Status: work in progress.** The P-only controller works. The I term, anti-windup
and D term are not written yet.

## Hardware

- Hosyond ESP32-S3 dev board (ESP32-S3-WROOM-1, N16R8)
- 1x LDR (photoresistor)
- 1x 10 kΩ resistor (LDR voltage divider)
- 1x LED with a 220–330 Ω series resistor
- Breadboard and jumper wires

### Pins

| Function | GPIO |
| --- | --- |
| LDR input (ADC1) | 5 |
| LED output (PWM) | 4 |

### Wiring

```
LDR divider:   3V3 ── LDR ──┬── GPIO5
                            │
                         10 kΩ
                            │
                           GND

LED:           GPIO4 ── 220–330 Ω ── LED (long leg) ── LED (short leg) ── GND
```

Face the LED toward the LDR a few cm away and shield both from room light.

Note: the board did not make reliable contact when seated in the breadboard.
Connecting the 3V3, GND, GPIO4 and GPIO5 pins with jumper wires fixed it.

## Build and run

Requires [PlatformIO](https://platformio.org/).

```
pio run                 # build
pio run -t upload       # flash (hold BOOT, tap RESET if it can't connect)
pio device monitor      # serial output at 115200 baud
```

Each loop prints one CSV line: `setpoint,y,u`

- `setpoint`: target LDR reading
- `y`: measured LDR reading (ADC, 0–4095)
- `u`: controller output (PWM duty, 0–255)

## Measurements

### Open loop (LED duty set by hand)

| Duty (u) | LDR reading (y) |
| --- | --- |
| 0 | ~200 (ymin) |
| 128 | ~1400 |
| 255 | ~1800 (ymax) |

The reachable range is about 200–1800, so the setpoint is 1000. The response
is not linear: duty 0–128 adds about 1200 counts, and 128–255 adds only about
400.

### Closed loop, P-only (setpoint = 1000)

| Kp | y settles at | Steady-state error | Behavior |
| --- | --- | --- | --- |
| 0.02 | ~420 | ~580 | stable |
| 0.05 | ~550 | ~450 | stable |
| 0.2 | ~800 | ~200 | stable |
| 0.5 | swings ~720–1300 | n/a | sustained oscillation |

The P term alone leaves a steady-state error, which shrinks as Kp grows. At
Kp = 0.5 the loop oscillates, so the ultimate gain Ku is about 0.5. Ziegler–Nichols
suggests starting around Kp ≈ 0.22–0.25.

## Next steps

- [ ] Set Kp back to about 0.2 and add the I term to remove the steady-state error
- [ ] Add anti-windup (clamp the integral)
- [ ] Use real elapsed time (`millis()`) instead of assuming a fixed `delay`
- [ ] Filter or average the noisy ADC readings
- [ ] Decide whether a D term helps
- [ ] Plot step responses and record rise time, overshoot and settling time
