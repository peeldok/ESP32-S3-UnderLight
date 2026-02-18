# UnderLight for ESP32 S3 - controlling LED strips via MIDI

This Arduino project uses the ESP32-S3 microcontroller to control an LED strip from a DAW program (via MIDI).
To upload a custom palette, please use the site to [Palette Upload](https://peeldok.github.io/ESP32-S3-UnderLight-PalettesUploader/)

## System Requirements

* LED Strip
	* The **WS2812B** strips are implemented in separate Arduino projects. 
* USB Development Board
    * [ESP32-S3](https://www.espressif.com/en/products/socs/esp32-s3)
* [Arduino Software](https://www.arduino.cc/en/Main/Software)
    * Developed with **version 1.8.5**, but older versions will likely work.
    * Also requires [FastLED Arduino library](https://github.com/FastLED/FastLED), and the [Control Surface](https://github.com/tttapa/Control-Surface)
* OS
    * **Windows, Linux and macOS** are officially supported.
* DAW Software
    * [Ableton Live](https://www.ableton.com/en/live/) is recommended due to its flexibility in creating MIDI Effects.

## Software
If you haven't already, install the Control Surface for Arduino and the FastLED library.

Modify the Arduino script according to your LED strip configuration (`_nLED` = Number of LEDs < 64 `_dLED` = Data pin)

In Tools, select USB Mode as USB-OTG (TinyUSB).

## PIN MAP

* LED Strip
	* PIN = 14
	* Power = 5V, Gnd

## Recommended for esp32s3
Solder the USB-OTG pads on the bottom.

Solder the N-OUT pads on the top. (Change the 5V input terminal to a 5V output terminal.)
