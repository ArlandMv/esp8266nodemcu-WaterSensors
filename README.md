[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?)](https://github.com/tterb/atomic-design-ui/blob/master/LICENSEs)

# Esp8266NodeMCU-WaterSensors

This equipment has the function of analyzing the largest possible number of sensors per nodemcu in locations where WiFi or Ethernet connectivity is not available. When detecting water, it alarms through common power cables (Relays).

## Author

- [@arlandmv](https://github.com/ArlandMv/)

## Optimizations

### Used millis() instead of delay()

First step to use FreeRTOS funtionality

### FreeRTOS usage

### Used available analog pin

Switched a sensor from pin D3 (GPIO) TO pin A0

## Acknowledgements

- [Rui Santos](https://youtu.be/LUcKoJGX38M) OTA sketch to do updates without opening device enclosure.
- [Best Pins to Use – ESP8266](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/) from Rui Santos' randomnerdtutorials.
- [rtos](https://youtu.be/k_D_Qu0cgu8)
- [octokatherine](https://github.com/octokatherine/readme.so) for easyiest way to write a README.md at [https://readme.so](https://readme.so/).

ntroduction to RTOS
https://youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz
