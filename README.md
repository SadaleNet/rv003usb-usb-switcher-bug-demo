# Demonstration of rv003usb USB Switcher Hub Bug

** Please visit the folder `demo_pikokey_hid` for the demo code **

Based on the PikoKey demo. Changes made:

* Adjusted USB_PORT, USB_PIN_DP, USB_PIN_DM, USB_PIN_DPU for my own hardware
* Made the variable `keypressed` volatile
* Added `__set_INTSYSCR( __get_INTSYSCR() | 0x02 );` to avoid the USB interrupt getting blocked by another interrupt.
* Removed unused functions in help_functions.h

