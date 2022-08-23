# Front Cam MQB DIY
DIY solution for Front Camera in MQB vehicle (VW Golf MK7).

## Concept
Adding Front Camera functionality to the vehicle, using universal 3rd party camera, some electronics, custom button. This tutorial is based on VW Golf MK7, factory equipped with Discover Media MIB2 system, with retrofitter RVC-High camera.

## Requirements
* Infotainment unit that supports Rear View Camera (units with part number ending with `819` and `820` does not support video feed input).
* Fitted and working RVC-High camera (RVC-Low camera video feed is switched of as soon as reverse gear is disenagaged, when RVC-High image is visible while moving forward with low speed).

## Parts
* Front camera in NTSC system
* * Option 1: https://s.click.aliexpress.com/e/_DkfmwDZ (not tested yet)
* * Option 2: https://s.click.aliexpress.com/e/_DFbM4L5
* ATTiny board - https://www.aliexpress.com/item/1005001621891306.html
* Relay: https://s.click.aliexpress.com/e/_Ddmhov9
* Wires, shrinking tubes, etc...

## Software
* Arduino IDE - https://www.arduino.cc
* OneButton library - https://github.com/mathertel/OneButton

## Installation
* Tapping into OEM buttons signals
* Enabling empty button
* Tapping into reverse gear signal
* Installing FrontCam
* Modifying OEM wiring by adding video feed switching relay
* Powering the controller with term_15

## Changelog
### `v0.1`
* initial release, not even tested in vehicle
* toggle button to switch between FrontCam and RVC
* automatic switching to front cam when reverse gear is disengaged

### `v0.2`
* memory of the FrontCam being switched of my user, reset after turning parktronic off.

### `v0.3`
* button detection fix
* sanity check for forced off function
* preparation for OneButton library
* variable typo fix

### `v0.4`
* OneButton library implementation
* Logging over Serial
* Single attempt to force turn on Parktronic if requested by the Front Cam button

## Future Concept
* Some cool feature for long-press event of the button, maybe?

## Reference and credits
* https://github.com/mathertel/OneButton
* https://www.golfmk7.com/forums/index.php?threads/diy-front-camera-upgrade-for-rvc-high.405296/
