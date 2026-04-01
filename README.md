# stm32-TablePet

A `PlatformIO + STM32Cube HAL` demo project for `STM32F103C8T6` driving a `GC9A01 240x240` round LCD over `SPI1`.

The project has been migrated from SPL to HAL and is currently in a buildable state with PlatformIO.

## Features

- `PlatformIO` based workflow
- `STM32Cube HAL` framework
- Target MCU: `STM32F103C8T6`
- LCD driver: `GC9A01`
- Resolution: `240x240`
- LCD interface: `SPI1`
- Debug UART: `USART1`
- Demo content:
  - display `LCD_W`
  - display `LCD_H`
  - display `Nun:`
  - update a float value every second

## Hardware

Recommended hardware:

- `STM32F103C8T6` development board
- `GC9A01 240x240` SPI round LCD
- `USB to TTL` serial adapter

### LCD Wiring

| LCD Signal | STM32 Pin |
| --- | --- |
| `SCL` | `PA5` |
| `SDA` | `PA7` |
| `RES` | `PA3` |
| `DC` | `PA2` |
| `CS` | `PA4` |
| `BLK` | `PA1` |

### UART Wiring

| UART Signal | STM32 Pin |
| --- | --- |
| `USART1_TX` | `PA9` |
| `USART1_RX` | `PA10` |

## Software

- Platform: `ststm32`
- Board: `genericSTM32F103C8`
- Framework: `stm32cube`

Project config file:

- [platformio.ini](E:\embed-project\stm32-TablePet\platformio.ini)

## Build

```bash
pio run
```

This project has already been verified to compile successfully with PlatformIO.

## Upload

Current serial upload configuration:

- `upload_protocol = serial`
- `upload_port = COM4`
- `upload_speed = 115200`

Command:

```bash
pio run -t upload
```

If your serial port is not `COM4`, update [platformio.ini](E:\embed-project\stm32-TablePet\platformio.ini) first.

## Serial Monitor

Current monitor configuration:

- `monitor_port = COM4`
- `monitor_speed = 115200`

Command:

```bash
pio device monitor
```

## Runtime Behavior

After power-up, the program does the following:

1. Initialize HAL and system clock
2. Initialize `USART1`
3. Initialize the LCD
4. Fill the screen with black
5. Continuously display:
   - `LCD_W`
   - `LCD_H`
   - `Nun:`
   - a float value incremented by `0.11` every second

Main entry:

- [main.c](E:\embed-project\stm32-TablePet\src\main.c)

## Project Structure

```text
stm32-TablePet/
|-- include/
|   |-- main.h
|   |-- stm32f1xx_hal_conf.h
|   `-- stm32f1xx_it.h
|-- src/
|   |-- main.c
|   |-- stm32f1xx_hal_msp.c
|   |-- stm32f1xx_it.c
|   |-- board/
|   |   |-- board.c
|   |   `-- board.h
|   `-- bsp/
|       |-- LCD/
|       |   |-- lcd.c
|       |   |-- lcd.h
|       |   |-- lcd_init.c
|       |   |-- lcd_init.h
|       |   |-- lcdfont.h
|       |   `-- pic.h
|       `-- uart/
|           |-- bsp_uart.c
|           `-- bsp_uart.h
|-- LICENSE
|-- README.md
|-- .gitignore
`-- platformio.ini
```

### Directory Overview

- `include/`
  - HAL public headers and interrupt declarations
- `src/board/`
  - board init, clock config, delay functions
- `src/bsp/LCD/`
  - LCD low-level driver and drawing functions
- `src/bsp/uart/`
  - `USART1` driver

## Notes

1. System clock is configured as `HSE 8MHz -> PLL x9 -> 72MHz`.
2. If the external crystal is not working correctly, the program may stop during clock initialization.
3. The LCD currently uses `SPI1` and the existing GC9A01 init sequence in the project.
4. If the backlight turns on but nothing is displayed, check these first:
   - LCD wiring
   - SPI timing/mode
   - LCD module compatibility
   - external crystal status

## Repository Status

- SPL legacy sources and libraries have been removed
- HAL migration has been completed
- PlatformIO build has been verified successfully
- `.gitignore` has been cleaned up for GitHub upload
- `MIT` license has been added

## Files Worth Keeping in Git

Core files and directories:

- [src](E:\embed-project\stm32-TablePet\src)
- [include](E:\embed-project\stm32-TablePet\include)
- [platformio.ini](E:\embed-project\stm32-TablePet\platformio.ini)
- [README.md](E:\embed-project\stm32-TablePet\README.md)
- [LICENSE](E:\embed-project\stm32-TablePet\LICENSE)
- [.gitignore](E:\embed-project\stm32-TablePet\.gitignore)

Normally ignored local/build content:

- `.pio/`
- `.pio-core/`
- most local `.vscode/` machine-specific files

## License

This project is licensed under the `MIT License`.

See:

- [LICENSE](E:\embed-project\stm32-TablePet\LICENSE)
