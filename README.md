Arduino DysonRemote
====================

Dependencies
------------

### Modules

* Three infrared LEDs
* DS1307: RTC module. Needed to read the current DateTime.
* L3G4200D: Gyroscope. Used to read current temp because I do not have a thermometer module.

### Libraries

* [RTClib](https://github.com/adafruit/RTClib): Read date time for DS1307
* [L3G4200D](https://github.com/jarzebski/Arduino-L3G4200D): Read temperature on L3G4200D

License
-------

DysonRemote is released under the MIT License. See the bundled LICENSE file for details.
