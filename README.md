
# STM32F1xx HD44780 Driver
This is a parallel driver for the HD44780 LCD specification on an STM32F1xx MCU. This driver was written for fun, I would recommend using vendor drivers for production use.

## Features
* Support for 1 or 2 16 character lines
* Able to read and write data to the controller
* Supports printf style formatting
* Word wrap
* Reverse printing
## API




**HD44780_Create**
Creates a HD44780_TypeDef to bind GPIO pins to the controller
Params:
 *  GPIOPort: Port used
 *  PinD0:    Data pin 0
 *  PinD1:    Data pin 1
 *  PinD2:    Data pin 2
 *  PinD3:    Data pin 3
 *  PinD4:    Data pin 4
 *  PinD5:    Data pin 5
 *  PinD6:    Data pin 6
 *  PinD7:    Data pin 7
 *  ENPin:    Enable pin
 *  RWPin:    Read/write pin
 *  RSPin:    Register select pin

Return: HDD44780_TypeDef to send commands to a screen


**HD44780_CreateFromBus**
Creates a HD44780_TypeDef to bind GPIO pins to the controller
Params:
 *  GPIOPort: Port used
 *  StartPin: Starting pin of the data line, the other lines will be set to each increasing pin
 *  ENPin:    Enable pin
 *  RWPin:    Read/write pin
 *  RSPin:    Register select pin

Return: HD44780_TypeDef to send commands to a screen


**HD44780_Init**
Initializes a controller
Params:
 * HD44780: HD44780 pin description
 * Options: 
`HD44780_INIT_BUS_SIZE_4`
`HD44780_INIT_BUS_SIZE_8`

	`HD44780_INIT_LINES_1`
	`HD44780_INIT_LINES_2`

	`HD44780_INIT_FONT_SIZE_SM`
	`HD44780_INIT_FONT_SIZE_LG`


**HD44780_DisplayMode**
Configures display settings
Params:
 * HD44780: HD44780 pin description
 * Options: 
`HD44780_DISPLAY_OFF`
`HD44780_DISPLAY_ON`

	`HD44780_DISPLAY_CURSOR_OFF`
	`HD44780_DISPLAY_CURSOR_ON`

	`HD44780_DISPLAY_BLINK_OFF`
	`HD44780_DISPLAY_BLINK_ON`


**HD44780_Direction**
Sets direction of text
Params:
 * HD44780: HD44780 pin description
 * Options:
`HD44780_DIRECTION_LEFT`
`HD44780_DIRECTION_RIGHT`


**HD44780_PrintChar**
Print a char on cursor location
Params:
 * HD44780: HD44780 pin description
 * c: Character to print


**HD44780_Printf**
Print a formatted string on cursor location
Params:
 * HD44780: HD44780 pin description
 * s: 	  String to print


**HD44780_Clear**
Clears the screen, sets cursor to the start
Params:
 * HD44780: HD44780 pin description


**HD44780_CursorRight**
Move cursor right
Params:
 * HD44780: HD44780 pin description


**HD44780_CursorLeft**
Move cursor left
Params:
 * HD44780: HD44780 pin description


**HD44780_CursorUp**
Move cursor up
Params:
 * HD44780: HD44780 pin description


**HD44780_CursorDown**
Move cursor down
Params:
 * HD44780: HD44780 pin description


**HD44780_MoveToPos**
Sets the cursor to a position
Params:
 * HD44780: HD44780 pin description
 * Pos:     Position to move to


**HD44780_MoveToLine**
Sets the cursor to the beginning of the selected line
Params:
 * HD44780: HD44780 pin description
 * Line:
`HD44780_LINE_1`
`HD44780_LINE_2`


**HD44780_SwitchLines**
Switch lines
Params:
 * HD44780: HD44780 pin description


