/*
 * stm32f1xx_HD44780_ex.h
 *
 *  Created on: Oct 9, 2020
 *      Author: aaronchambers
 */

#ifndef __STM32F1XX_HD44780_EX_DEF
#define __STM32F1XX_HD44780_EX_DEF

#include "stm32f1xx_HD44780.h"

void HD44780_SetData(HD44780_TypeDef *HD44780, uint8_t Data);
void HD44780_Send(HD44780_TypeDef *HD44780);
void HD44780_SendData(HD44780_TypeDef *HD44780, uint8_t Data);

void HD44780_Read(HD44780_TypeDef *HD44780, char *str);

void HD44780_WriteRS(HD44780_TypeDef *HD44780, uint8_t State);

uint8_t HD44780_PosOffscreen(uint16_t Pos);
uint8_t HD44780_CursorOffscreen(HD44780_TypeDef *HD44780);

#endif /* __STM32F1XX_HD44780_EX_DEF */
