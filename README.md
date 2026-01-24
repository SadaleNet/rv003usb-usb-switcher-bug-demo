# Demonstration of rv003usb USB Switcher Hub Bug

Two demo of the bug.

1. demo_pikokey_hid

Based on the PikoKey demo. Changes made:

* Removed button detection mechanism. Made the device tap 'a' for 100ms once a second.
* Adjusted USB_PORT, USB_PIN_DP, USB_PIN_DM, USB_PIN_DPU for my own hardware
* Made the variable `keypressed` volatile
* Added `__set_INTSYSCR( __get_INTSYSCR() | 0x02 );` to avoid the USB interrupt getting blocked by another interrupt.
* Removed unused functions in help_functions.h
* Reduced the Delay_Ms at the initialization from 100ms to 1ms

2. demo_composite_hid

Based on the PikoKey demo. Changes made:

* Adjusted USB_PORT, USB_PIN_DP, USB_PIN_DM, USB_PIN_DPU for my own hardware
* Removed mouse input mechanism
