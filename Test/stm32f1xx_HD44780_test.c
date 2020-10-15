/*
 * stm32f1xx_HD44780_test.c
 *
 *  Created on: Oct 10, 2020
 *      Author: aaronchambers
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "stm32f1xx_HD44780_test.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

extern void initialise_monitor_handles(void);

int testWrite()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780 Driver");
	HD44780_SwitchLines(&HD44780);
	HD44780_Printf(&HD44780, "Test: 01");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 01        ")==0);
}

int testClear()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780 Driver");
	HD44780_SwitchLines(&HD44780);
	HD44780_Printf(&HD44780, "Test: 02");
	HD44780_Clear(&HD44780);

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "                                ")==0);
}

int testReverseWrite()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Direction(&HD44780, HD44780_DIRECTION_LEFT);
	HD44780_MoveToPos(&HD44780, HD44780_LINE_2 + 15);
	HD44780_Printf(&HD44780, "        30 :tseT");
	HD44780_Printf(&HD44780, "  revirD 08744DH");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 03        ")==0);
}

int testWordWrap()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780 Driver  Test: 04");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 04        ")==0);
}

int testReverseWrap()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Direction(&HD44780, HD44780_DIRECTION_LEFT);
	HD44780_Printf(&HD44780, "         50 :tseT  revirD 08744DH");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 05        ")==0);
}

int testSetPosition()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780");
	HD44780_MoveToPos(&HD44780, 8);
	HD44780_Printf(&HD44780, "Driver");
	HD44780_MoveToPos(&HD44780, HD44780_LINE_2);
	HD44780_Printf(&HD44780, "Test: 06");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 06        ")==0);
}

int testSetLine()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_MoveToLine(&HD44780, HD44780_LINE_2);
	HD44780_Printf(&HD44780, "Test: 07");
	HD44780_MoveToLine(&HD44780, HD44780_LINE_1);
	HD44780_Printf(&HD44780, "HD44780 Driver");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 07        ")==0);
}

int testSeparatedBus()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_Create(GPIOA, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, 
    GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780 Driver");
	HD44780_SwitchLines(&HD44780);
	HD44780_Printf(&HD44780, "Test: 08");

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 08        ")==0);
}

int testPrintfFormatting()
{
	char str[33];

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "HD44780 %s", "Driver");
	HD44780_SwitchLines(&HD44780);
	HD44780_Printf(&HD44780, "Test: %02i", 9);

	HD44780_Read(&HD44780, str);

	return (strcmp(str, "HD44780 Driver  Test: 09        ")==0);
}



void testsPassed()
{
	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_LG);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_Printf(&HD44780, "Hello World!");
	HD44780_SwitchLines(&HD44780);
	HD44780_Printf(&HD44780, "HD44780 Driver");

	printf("All tests pass\n");
}

int main(void)
{

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();

	uint8_t arr[] = {
		0b00000,
		0b01010,
		0b10101,
		0b10001,
		0b01010,
		0b00100,
		0b00000,
		0b00000
	};

	initialise_monitor_handles();

	HD44780_TypeDef HD44780 = HD44780_CreateFromBus(GPIOA, GPIO_PIN_0, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12);

	HD44780_Init(&HD44780, HD44780_INIT_BUS_SIZE_8 | HD44780_INIT_LINES_2 | HD44780_INIT_FONT_SIZE_SM);
	HD44780_DisplayMode(&HD44780, HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR_ON | HD44780_DISPLAY_BLINK_OFF);
	HD44780_RegisterCustomChar(&HD44780, 0, arr);
	HD44780_PrintCustomChar(&HD44780, 0);
	//HD44780_Printf(&HD44780, "HD44780 Driver");
	HD44780_SwitchLines(&HD44780);
	//HD44780_Printf(&HD44780, "Test: 01");


	// assert(testWrite());
	// printf("Write test passed\n");

	// assert(testClear());
	// printf("Clear test passed\n");

	// assert(testReverseWrite());
	// printf("Reverse write test passed\n");

	// assert(testWordWrap());
	// printf("Word wrap test passed\n");

	// assert(testReverseWrap());
	// printf("Reverse wrap test passed\n");

	// assert(testSetPosition());
	// printf("Set position test passed\n");

	// assert(testSetLine());
	// printf("Set line test passed\n");

	// assert(testSeparatedBus());
	// printf("Separated bus test passed\n");

	// assert(testPrintfFormatting());
	// printf("Printf Formatting test passed\n");

	// testsPassed();

	while (1) {}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

static void MX_GPIO_Init(void)
{

	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

void Error_Handler(void)
{

}
