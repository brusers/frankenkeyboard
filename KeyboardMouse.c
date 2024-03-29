/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
		Websites for key codes
http://www.fourwalledcubicle.com/files/LUFA/Doc/130303/html/group___group___u_s_b_class_h_i_d_common.html#ga9094a4f76840f1ef8d688cd729935d47

		Tuomas's keyboard thing
https://github.com/tuomasnylund/usb-numpad/blob/master/code/main.c#L154

		Shift register website
http://dduino.blogspot.fi/2012/04/arduino-74hc165-psio-shift-regsiter.html
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the KeyboardMouse demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include <stdint.h>
#include <avr/pgmspace.h>
#include "KeyboardMouse.h"
#include "key_codes.h"

void scanMatrix(uint8_t *myArray, uint8_t num);

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** Buffer to hold the previously generated Mouse HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another. This is for the keyboard HID
 *  interface within the device.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = 0,
				.ReportINEndpoint             =
					{
						.Address              = KEYBOARD_IN_EPADDR,
						.Size                 = HID_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
			},
	};

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another. This is for the mouse HID
 *  interface within the device.
 */
USB_ClassInfo_HID_Device_t Mouse_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = 1,
				.ReportINEndpoint             =
					{
						.Address              = MOUSE_IN_EPADDR,
						.Size                 = HID_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevMouseHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevMouseHIDReportBuffer),
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	uint32_t myBits = 0;
	SetupHardware();
	GlobalInterruptEnable();

	for (;;)
	{	
		HID_Device_USBTask(&Keyboard_HID_Interface);
		HID_Device_USBTask(&Mouse_HID_Interface);
		USB_USBTask();
	}
}


/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
	DDRD&= ~(1<<DDD3);	// disable PD3 for input, serial in
	DDRD|= (1<<DDD4);	// enable PD4 as output, LED
	DDRD|= (1<<DDD5);	// enable PD5 as output, EN
	DDRD|= (1<<DDD6);	// enable PD6 as output, RIN_CLK
	DDRD&= ~(1<<DDD7);	// Button
	DDRB|= (1<<DDB0);
	DDRB|= (1<<DDB1);
	DDRB|= (1<<DDB2);
	DDRB|= (1<<DDB4);
	DDRB|= (1<<DDB5);
	DDRB|= (1<<DDB6);
	DDRB|= (1<<DDB7);
	DDRC|= (1<<DDC5);
	DDRC|= (1<<DDC6);	// enable PB1 as output
	DDRC|= (1<<DDC7);	// enable PD2 as output
	
	LED_OFF;
	ROUT_CLK_DOWN;
	RIN_CLK_DOWN;			
	EN_DOWN;
	
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	//~ Joystick_Init();
	//~ LEDs_Init();
	USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
    //~ LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
    //~ LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);

	USB_Device_EnableSOFEvents();

	//~ LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
	HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
	HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	//~ uint8_t JoyStatus_LCL    = Joystick_GetStatus();
	//~ uint8_t ButtonStatus_LCL = Buttons_GetStatus();

	/* Determine which interface must have its report generated */
	if (HIDInterfaceInfo == &Keyboard_HID_Interface)
	{
		uint8_t key = 0;	
		USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
		
		for (uint8_t n=0;n<10;n++){
			uint8_t temp[5]={};
			scanMatrix(temp, n);
			for (uint8_t i = 0; i<5; i++){
				if (temp[i] != 0) KeyboardReport->KeyCode[key++] = temp[i];
			}
			if (key == 5) goto DONE;
		}
		//~ scanMatrix(temp, 2);
		//~ for (uint8_t i = 0; i<5; i++){
			//~ if (temp[i] != 0) KeyboardReport->KeyCode[key++] = temp[i];
		//~ }
		//~ if (key == 5) goto DONE;
		
		//if (!(1<<PD7 & PIND)) KeyboardReport->Modifier = HID_KEYBOARD_LED_CAPSLOCK; //HID_KEYBOARD_MODIFIER_LEFTSHIFT;
		
		//KeyboardReport->KeyCode[0] = temp[0];
		//KeyboardReport->KeyCode[1] = temp[1];

		//~ /* If first board button not being held down, no keyboard report */
		//~ if (!(ButtonStatus_LCL & BUTTONS_BUTTON1))
		  //~ return 0;

		// KeyboardReport->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;

		//~ if (JoyStatus_LCL & JOY_UP)
		  //~ KeyboardReport->KeyCode[0] = HID_KEYBOARD_SC_A;
		//~ else if (JoyStatus_LCL & JOY_DOWN)
		  //~ KeyboardReport->KeyCode[0] = HID_KEYBOARD_SC_B;
//~ 
		//~ if (JoyStatus_LCL & JOY_LEFT)
		  //~ KeyboardReport->KeyCode[0] = HID_KEYBOARD_SC_C;
		//~ else if (JoyStatus_LCL & JOY_RIGHT)
		  //~ KeyboardReport->KeyCode[0] = HID_KEYBOARD_SC_D;
//~ 
		//~ if (JoyStatus_LCL & JOY_PRESS)
		  //~ KeyboardReport->KeyCode[0] = HID_KEYBOARD_SC_E;
		DONE:
		*ReportSize = sizeof(USB_KeyboardReport_Data_t);
		return false;
	}
	
	else
	{
		USB_MouseReport_Data_t* MouseReport = (USB_MouseReport_Data_t*)ReportData;

		//~ /* If first board button being held down, no mouse report */
		//~ if (ButtonStatus_LCL & BUTTONS_BUTTON1)
		  //~ return 0;
//~ 
		//~ if (JoyStatus_LCL & JOY_UP)
		  //~ MouseReport->Y = -1;
		//~ else if (JoyStatus_LCL & JOY_DOWN)
		  //~ MouseReport->Y =  1;
//~ 
		//~ if (JoyStatus_LCL & JOY_LEFT)
		  //~ MouseReport->X = -1;
		//~ else if (JoyStatus_LCL & JOY_RIGHT)
		  //~ MouseReport->X =  1;
//~ 
		//~ if (JoyStatus_LCL & JOY_PRESS)
		
		
		
		//if (button_map == 10)
		//	MouseReport->Button |= (1 << 0);			// left click
		//if (button_map == 10)
		//	MouseReport->Button |= (2 << 0);			// right click
		//if (button_map == 10)
			//MouseReport->Button |= (4 << 0);			// middle click
						
		*ReportSize = sizeof(USB_MouseReport_Data_t);
		return true;
	}
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	if (HIDInterfaceInfo == &Keyboard_HID_Interface)
	{
		//~ uint8_t  LEDMask   = LEDS_NO_LEDS;
		//~ uint8_t* LEDReport = (uint8_t*)ReportData;

		//~ if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
		  //~ LEDMask |= LEDS_LED1;
//~ 
		//~ if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
		  //~ LEDMask |= LEDS_LED3;
//~ 
		//~ if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
		  //~ LEDMask |= LEDS_LED4;
//~ 
		//~ LEDs_SetAllLEDs(LEDMask);
	}
}


void scanMatrix(uint8_t *myArray, uint8_t num){
	uint8_t n = 0;
	
	if (num==0) COL_1_UP;
	else if (num==1) COL_2_UP;
	else if (num==2) COL_3_UP;
	else if (num==3) COL_4_UP;
	else if (num==4) COL_5_UP;
	else if (num==5) COL_6_UP;
	else if (num==6) COL_7_UP;
	else if (num==7) COL_8_UP;
	else if (num==8) COL_9_UP;
	else if (num==9) COL_10_UP;
	
	EN_UP;									// enable, ready to shift
	for(int8_t i=0; i<18; i++){
		if (1<<PD3 & PIND){
			//if (keyMatrix[num][i] != 0) myArray[n] = keyMatrix[num][i];
			if (pgm_read_byte(&keyMatrix[num][i]) != 0) myArray[n] = pgm_read_byte(&keyMatrix[num][i]);
			n++;
		}
	RIN_CLK_UP;
	_delay_us(10);
	RIN_CLK_DOWN;
	_delay_us(10);
	}
	EN_DOWN;

	COL_1_DOWN;
	COL_2_DOWN;
	COL_3_DOWN;
	COL_4_DOWN;
	COL_5_DOWN;
	COL_6_DOWN;
	COL_7_DOWN;
	COL_8_DOWN;
	COL_9_DOWN;
	COL_10_DOWN;
}
	// check that it does not exceed 5 keys.

