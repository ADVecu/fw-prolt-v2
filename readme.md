# PROLT-V2 rusEFI firmware

Custom rusEFI firmware for the PROLT-V2 ECU (STM32F407VGT6, 32-pin Molex connector).
Hardware: https://github.com/ADVecu/PROLT-V2

rusEFI is pinned to the official release tag `release_20260812` in `ext/rusefi`.
Do not move it to master: update it only to a newer `release_*` tag.

Build locally:

```
bash bin/_init.sh
bash compile_firmware.sh
```

See https://github.com/rusefi/rusefi/wiki/Custom-Firmware

## Hardware QC board overrides

[firmware/hardware/board_hw_test.cpp](firmware/hardware/board_hw_test.cpp)
lists the board outputs for the hardware QC / bench test.
