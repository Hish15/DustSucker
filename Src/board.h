#pragma once
#include <stm32h7xx_hal.h>
#include "main.h"
class Board
{
    public:
        void TurnOnLED1()
        {

        }
    private:
        void LEDInit()
        {
            GPIO_InitTypeDef  GPIO_InitStruct;

            /* Enable the GPIO_LED Clock */
            __HAL_RCC_GPIOB_CLK_ENABLE();
            /* Configure the GPIO_LED pin */
            GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        }

};
