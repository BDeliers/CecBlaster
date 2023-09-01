CEC Blaster
===========

**BDeliers - 2023**

HDMI CEC bridge based on STM32H563.

Using a Nucleo-STM32H563ZI board, CEC commands from the TV/playback device are interpreted to control a non-CEC home cinema receiver over IR.

My setup: 
- Orange UHD TV decoder
- Samsung UE43TU7125 TV
- Sony 5.1 home cinema receiver STR-DG510

Pinout on the Nucleo board: 
- CEC is on PB6
- IR diode is on PE9
- User button is on PC13

Schematics in the Schematic.pdf file
