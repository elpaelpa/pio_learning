# ESP32 Experiments with PlatformIO

PlatformIO and ESP32 experiments. Each experiment is its own folder with its own
`platformio.ini` and README, covering wiring, results and notes.

## Experiments

| Experiment | Description | Status |
| --- | --- | --- |
| [light_pid_controller](light_pid_controller/) | LDR + LED closed-loop brightness control on an ESP32-S3, tuning a PID controller | In progress (P-only works) |

## Hardware

- Hosyond ESP32-S3 dev board (ESP32-S3-WROOM-1, N16R8)
- Breadboard, jumper wires, resistors, LEDs, LDR

## Working with the experiments

Requires [PlatformIO](https://platformio.org/). Open **one experiment folder at a time**
as the VS Code workspace (the folder that contains `platformio.ini`), not the
repo root.

```
cd <experiment folder>
pio run                 # build
pio run -t upload       # flash (hold BOOT, tap RESET if it can't connect)
pio device monitor      # serial output
```

## Adding a new experiment

1. Create a new folder next to the existing ones (e.g. `my_new_experiment/`).
2. Create a PlatformIO project inside it, with the board and Arduino framework.
3. Add a `README.md` to it, and add a row to the table above.
