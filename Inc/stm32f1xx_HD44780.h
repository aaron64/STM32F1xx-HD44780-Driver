/*
 * stm32f1xx_HD44780.h
 *
 *  Created on: Oct 8, 2020
 *      Author: aaronchambers
 */

#ifndef __STM32F1XX_HD44780_DEF
#define __STM32F1XX_HD44780_DEF

#include "stm32f1xx_hal.h"

typedef struct
{
	GPIO_TypeDef *GPIOPort;		// GPIO Port for data pins

	uint32_t PinD0;				// Data pin 0 for the controller
	uint32_t PinD1;				// Data pin 1 for the controller
	uint32_t PinD2;				// Data pin 2 for the controller
	uint32_t PinD3;				// Data pin 3 for the controller
	uint32_t PinD4;				// Data pin 4 for the controller
	uint32_t PinD5;				// Data pin 5 for the controller
	uint32_t PinD6;				// Data pin 6 for the controller
	uint32_t PinD7;				// Data pin 7 for the controller

	uint32_t PinEN;				// Enable pin for the controller
	uint32_t PinRW;				// Read write pin for the controller
	uint32_t PinRS;				// Register select pin for the controller

	uint16_t Pos;				// Current cursor position
	int8_t Direction;			// Direction the cursor moves
} HD44780_TypeDef;

#define HD44780_SEGMENTS			16

#define HD44780_SPEED				1
#define HD44780_READ_SPEED			4

#define HD44780_INIT_BUS_SIZE_4		0
#define HD44780_INIT_BUS_SIZE_8		16

#define HD44780_INIT_LINES_1		0
#define HD44780_INIT_LINES_2		8

#define HD44780_LINE_1 				0
#define HD44780_LINE_2 				64

#define HD44780_INIT_FONT_SIZE_SM	0
#define HD44780_INIT_FONT_SIZE_LG	4

#define HD44780_DISPLAY_OFF			0
#define HD44780_DISPLAY_ON			4
#define HD44780_DISPLAY_CURSOR_OFF	0
#define HD44780_DISPLAY_CURSOR_ON	2
#define HD44780_DISPLAY_BLINK_OFF	0
#define HD44780_DISPLAY_BLINK_ON	1

#define HD44780_DIRECTION_LEFT		0
#define HD44780_DIRECTION_RIGHT		2

#define HD44780_SHIFT_DISPLAY		0
#define HD44780_SHIFT_CURSOR		8
#define HD44780_SHIFT_RIGHT			0
#define HD44780_SHIFT_LEFT			4

#define HD44780_RS_DI				0
#define HD44780_RS_EN				1

#define HD44780_FUNCTION_CLEAR		0b00000001
#define HD44780_FUNCTION_HOME		0b00000010
#define HD44780_FUNCTION_ENTRY_MODE	0b00000100
#define HD44780_FUNCTION_DISPLAY	0b00001000
#define HD44780_FUNCTION_SHIFT		0b00010000
#define HD44780_FUNCTION_INIT		0b00100000
#define HD44780_FUNCTION_SET_CGRAM	0b01000000
#define HD44780_FUNCTION_SET_DDRAM	0b10000000

/**
 * Creates a HD44780_TypeDef to bind GPIO pins to the controller
 * @param  GPIOPort Port used
 * @param  PinD0    Data pin 0
 * @param  PinD1    Data pin 1
 * @param  PinD2    Data pin 2
 * @param  PinD3    Data pin 3
 * @param  PinD4    Data pin 4
 * @param  PinD5    Data pin 5
 * @param  PinD6    Data pin 6
 * @param  PinD7    Data pin 7
 * @param  ENPin    Enable pin
 * @param  RWPin    Read/write pin
 * @param  RSPin    Register select pin
 * @return          HDD44780_TypeDef to send commands to a screen
 */
HD44780_TypeDef HD44780_Create(GPIO_TypeDef *GPIOPort, uint32_t PinD0, uint32_t PinD1, uint32_t PinD2, uint32_t PinD3, uint32_t PinD4, uint32_t PinD5, uint32_t PinD6, uint32_t PinD7, uint32_t ENPin, uint32_t RWPin, uint32_t RSPin);

/**
 * Creates a HD44780_TypeDef to bind GPIO pins to the controller
 * @param  GPIOPort Port used
 * @param  StartPin Starting pin of the data line, the other lines will be set to each increasing pin
 * @param  ENPin    Enable pin
 * @param  RWPin    Read/write pin
 * @param  RSPin    Register select pin
 * @return          HD44780_TypeDef to send commands to a screen
 */
HD44780_TypeDef HD44780_CreateFromBus(GPIO_TypeDef *GPIOPort, uint32_t StartPin, uint32_t ENPin, uint32_t RWPin, uint32_t RSPin);

/**
 * Initializes a controller
 * @param HD44780 HD44780 pin description
 * @param Options 
 *      HD44780_INIT_BUS_SIZE_4
 *		HD44780_INIT_BUS_SIZE_8
 *		
 *		HD44780_INIT_LINES_1
 *		HD44780_INIT_LINES_2
 *		
 *		HD44780_INIT_FONT_SIZE_SM
 *		HD44780_INIT_FONT_SIZE_LG
 */
void HD44780_Init(HD44780_TypeDef *HD44780, uint8_t Options);

/**
 * Configures display settings
 * @param HD44780 HD44780 pin description
 * @param Options 
 *      HD44780_DISPLAY_OFF
 *		HD44780_DISPLAY_ON
 *		
 *		HD44780_DISPLAY_CURSOR_OFF
 *		HD44780_DISPLAY_CURSOR_ON
 *		
 *		HD44780_DISPLAY_BLINK_OFF
 *		HD44780_DISPLAY_BLINK_ON
 */
void HD44780_DisplayMode(HD44780_TypeDef *HD44780, uint8_t Options);

/**
 * Sets direction of text
 * @param HD44780 HD44780 pin description
 * @param Options
 * 		HD44780_DIRECTION_LEFT
 * 		HD44780_DIRECTION_RIGHT
 */
void HD44780_Direction(HD44780_TypeDef *HD44780, uint8_t Options);

/**
 * Print a char on cursor location
 * @param HD44780 HD44780 pin description
 * @param 		  c Character to print
 */
void HD44780_PrintChar(HD44780_TypeDef *HD44780, char c);

/**
 * Print a formatted string on cursor location
 * @param HD44780 HD44780 pin description
 * @param s 	  String to print
 */
void HD44780_Printf(HD44780_TypeDef *HD44780, char *s, ...);

/**
 * Clears the screen, sets cursor to the start
 * @param HD44780 HD44780 pin description
 */
void HD44780_Clear(HD44780_TypeDef *HD44780);

/**
 * Move cursor right
 * @param HD44780 HD44780 pin description
 */
void HD44780_CursorRight(HD44780_TypeDef *HD44780);

/**
 * Move cursor left
 * @param HD44780 HD44780 pin description
 */
void HD44780_CursorLeft(HD44780_TypeDef *HD44780);

/**
 * Move cursor up
 * @param HD44780 HD44780 pin description
 */
void HD44780_CursorUp(HD44780_TypeDef *HD44780);

/**
 * Move cursor down
 * @param HD44780 HD44780 pin description
 */
void HD44780_CursorDown(HD44780_TypeDef *HD44780);

/**
 * Sets the cursor to a position
 * @param HD44780 HD44780 pin description
 * @param Pos     Position to move to
 */
void HD44780_MoveToPos(HD44780_TypeDef *HD44780, uint8_t Pos);

/**
 * Sets the cursor to the beginning of the selected line
 * @param HD44780 HD44780 pin description
 * @param Line
 *        HD44780_LINE_1
 *        HD44780_LINE_2
 */
void HD44780_MoveToLine(HD44780_TypeDef *HD44780, uint8_t Line);

/**
 * Switch lines
 * @param HD44780 HD44780 pin description
 */
void HD44780_SwitchLines(HD44780_TypeDef *HD44780);

#endif /* __STM32F1XX_HD44780_DEF */
