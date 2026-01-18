#include "ch32fun.h"
#include <stdio.h>
#include <string.h>
#include "rv003usb.h"
#include "help_functions.h"
// ./minichlink -D to use nrst, also PD1 needs pullup 

volatile uint8_t keypressed[8] = {0};
int main()
{
	SystemInit();
	// Enable interrupt nesting for rv003usb software USB library
	__set_INTSYSCR( __get_INTSYSCR() | 0x02 );

	Delay_Ms(100); // Ensures USB re-enumeration after bootloader or reset; Spec demand >2.5µs ( TDDIS )
	systick_init();

	usb_setup();
	uint32_t prev_time = GetSystemTime();
	for(uint8_t k=0;k<6;k++){
		keypressed[2+k]=0;
	}

	while(1)
	{
#if RV003USB_EVENT_DEBUGGING
		uint32_t * ue = GetUEvent();
		if( ue )
		{
			printf( "%lu %lx %lx %lx\n", ue[0], ue[1], ue[2], ue[3] );
		}
#endif
		uint32_t current_time = GetSystemTime();
		if(current_time-prev_time < 100) {
			keypressed[2]=0x04; // HID_KEY_A
		} else if(current_time-prev_time < 1000) {
			keypressed[2]=0;
		} else {
			prev_time = current_time;
		}

		Delay_Us(10); // Smaller is better, but too small causes hanging. Increase this delay when key map larger.

	}
}
int i=0;
uint8_t tsajoystick[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

void usb_handle_user_in_request( struct usb_endpoint * e, uint8_t * scratchpad, int endp, uint32_t sendtok, struct rv003usb_internal * ist )
{
	if( endp == 1 )
	{
		i++;
		// if(keypressed[0] == 1){
			tsajoystick[0] = keypressed[1];
			for(uint8_t k=0;k<6;k++){
				tsajoystick[2+k] = keypressed[2+k];
				// keypressed[2+k]=0;
			}
			// keypressed[1] = 0;
			// keypressed[0] = 0;
		// }
		usb_send_data( tsajoystick, 8, 0, sendtok );
		for(uint8_t k=0;k<8;k++){
			tsajoystick[k] = 0;
		}
		}
	else
	{
		usb_send_empty( sendtok );
	}
}


