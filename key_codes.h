#ifndef _KEY_CODES_H_
#define _KEY_CODES_H_


#define SERIAL_OUT_UP PORTB|=(1<<PORTB1)			// SERIAL_OUT_UP
#define SERIAL_OUT_DOWN PORTB&=~(1<<PORTB1)			// SERIAL_OUT_DOWN
#define ROUT_CLK_UP PORTD|=(1<<PORTD2)				// ROUt_CLK_UP
#define ROUT_CLK_DOWN PORTD&=~(1<<PORTD2)			// ROUT_CLK_DOWN
#define LED_ON PORTD|=(1<<PORTD4)					// LED_ON
#define LED_OFF PORTD&=~(1<<PORTD4)					// LED_OFF
#define EN_UP PORTD|=(1<<PORTD5)					// EN_UP
#define EN_DOWN PORTD&=~(1<<PORTD5)					// EN_DOWN
#define RIN_CLK_UP PORTD|=(1<<PORTD6)				// RIN_CLK_UP
#define RIN_CLK_DOWN PORTD&=~(1<<PORTD6)			// RIN_CLK_DOWN

#define COL_1_UP PORTB|=(1<<PORTB0)
#define COL_1_DOWN PORTB&=~(1<<PORTB0)
#define COL_2_UP PORTB|=(1<<PORTB1)
#define COL_2_DOWN PORTB&=~(1<<PORTB1)
#define COL_3_UP PORTB|=(1<<PORTB2)
#define COL_3_DOWN PORTB&=~(1<<PORTB2)
#define COL_4_UP PORTB|=(1<<PORTB4)
#define COL_4_DOWN PORTB&=~(1<<PORTB4)
#define COL_5_UP PORTB|=(1<<PORTB5)
#define COL_5_DOWN PORTB&=~(1<<PORTB5)
#define COL_6_UP PORTB|=(1<<PORTB6)
#define COL_6_DOWN PORTB&=~(1<<PORTB6)
#define COL_7_UP PORTB|=(1<<PORTB7)
#define COL_7_DOWN PORTB&=~(1<<PORTB7)
#define COL_8_UP PORTC|=(1<<PORTC7)
#define COL_8_DOWN PORTC&=~(1<<PORTC7)
#define COL_9_UP PORTC|=(1<<PORTC6)
#define COL_9_DOWN PORTC&=~(1<<PORTC6)
#define COL_10_UP PORTC|=(1<<PORTC5)
#define COL_10_DOWN PORTC&=~(1<<PORTC5)

const uint8_t keyMatrix[10][18] PROGMEM = {
/*Col 1*/	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

/*Col 2*/	{HID_KEYBOARD_SC_H, HID_KEYBOARD_SC_F6, HID_KEYBOARD_SC_F5, 0, HID_KEYBOARD_SC_G, HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE, 
				HID_KEYBOARD_SC_F4, 0, 0, 0, HID_KEYBOARD_SC_ESCAPE, HID_KEYBOARD_SC_PAGE_UP, 0, HID_KEYBOARD_SC_UP_ARROW, 0, 
				HID_KEYBOARD_SC_LEFT_ALT, 0, 0},
				
/*Col 3*/	{HID_KEYBOARD_SC_6_AND_CARET, HID_KEYBOARD_SC_EQUAL_AND_PLUS, HID_KEYBOARD_SC_F9, HID_KEYBOARD_SC_F8, HID_KEYBOARD_SC_5_AND_PERCENTAGE, 
				HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE, HID_KEYBOARD_SC_F2, HID_KEYBOARD_SC_DELETE, HID_KEYBOARD_SC_F1, HID_KEYBOARD_SC_INSERT,
				HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE, 0, 0, HID_KEYBOARD_SC_HOME, HID_KEYBOARD_SC_LEFT_CONTROL, 0, 0, 0},
				
/*Col 4*/	{HID_KEYBOARD_SC_Y, HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE, HID_KEYBOARD_SC_BACKSPACE, HID_KEYBOARD_SC_F7,
				HID_KEYBOARD_SC_T, HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE, HID_KEYBOARD_SC_F3, HID_KEYBOARD_SC_VOLUME_DOWN,
				HID_KEYBOARD_SC_CAPS_LOCK, 0, HID_KEYBOARD_SC_TAB, 0, HID_KEYBOARD_SC_LEFT_SHIFT, 0, 0, 0, 0, 0},
				
/*Col 5*/	{HID_KEYBOARD_SC_U, HID_KEYBOARD_SC_I, 0, HID_KEYBOARD_SC_O, HID_KEYBOARD_SC_R, HID_KEYBOARD_SC_P, HID_KEYBOARD_SC_E,
				HID_KEYBOARD_SC_VOLUME_UP, HID_KEYBOARD_SC_W, 0, HID_KEYBOARD_SC_Q, HID_KEYBOARD_SC_LEFT_GUI, 0, 0, 0,
				HID_KEYBOARD_SC_SCROLL_LOCK, 0, 0},
				
/*Col 6*/	{HID_KEYBOARD_SC_J, HID_KEYBOARD_SC_K, HID_KEYBOARD_SC_BACKSLASH_AND_PIPE, HID_KEYBOARD_SC_L, HID_KEYBOARD_SC_F,
				HID_KEYBOARD_SC_SEMICOLON_AND_COLON, HID_KEYBOARD_SC_D, HID_KEYBOARD_SC_MUTE, HID_KEYBOARD_SC_S, 0, HID_KEYBOARD_SC_A,
				0, 0, 0, 0, 0, 0, 0},
				
/*Col 7*/	{HID_KEYBOARD_SC_7_AND_AND_AMPERSAND, HID_KEYBOARD_SC_8_AND_ASTERISK, HID_KEYBOARD_SC_F10, HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
				HID_KEYBOARD_SC_4_AND_DOLLAR, HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS, HID_KEYBOARD_SC_3_AND_HASHMARK, HID_KEYBOARD_SC_F11, 
				HID_KEYBOARD_SC_2_AND_AT, HID_KEYBOARD_SC_F12, HID_KEYBOARD_SC_1_AND_EXCLAMATION, HID_KEYBOARD_SC_PAGE_DOWN, 0, HID_KEYBOARD_SC_END,
				0, HID_KEYBOARD_SC_PRINT_SCREEN, 0, 0},
				
/*Col 8*/	{HID_KEYBOARD_SC_M, HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN, HID_KEYBOARD_SC_ENTER, HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
				HID_KEYBOARD_SC_V, 0, HID_KEYBOARD_SC_C, 0, HID_KEYBOARD_SC_X, 0, HID_KEYBOARD_SC_Z, 0, HID_KEYBOARD_SC_RIGHT_SHIFT,
				HID_KEYBOARD_SC_PAUSE, HID_KEYBOARD_SC_RIGHT_CONTROL, 0, 0, 0},
				
/*Col 9*/	{HID_KEYBOARD_SC_N, 0, HID_KEYBOARD_SC_SPACE, 0, HID_KEYBOARD_SC_B, HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK, 0,
				HID_KEYBOARD_SC_DOWN_ARROW, 0, HID_KEYBOARD_SC_RIGHT_ARROW, 0, 0, 0, HID_KEYBOARD_SC_LEFT_ARROW, 0,
				HID_KEYBOARD_SC_RIGHT_ALT, 0, 0},
				
/*Col 10*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, HID_KEYBOARD_SC_POWER, 0}
};


#endif
// Tuomas reads cosmopolitan.. 
