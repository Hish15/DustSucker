#include "wheel.h"

Wheel::Wheel(GPIO_TypeDef* forwardPort, uint16_t forwardPin, GPIO_TypeDef* backwardPort, uint16_t backwardPin)
{
    _forwardPort = forwardPort;
    _forwardPin = forwardPin;
    _backwardPort = backwardPort;
    _backwardPin =  backwardPin;

    GPIO_InitTypeDef  GPIO_InitStruct = {0};

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_InitStruct.Pin = forwardPin;
    HAL_GPIO_Init(forwardPort, &GPIO_InitStruct);
    HAL_GPIO_WritePin(forwardPort, forwardPin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = backwardPin;
    HAL_GPIO_Init(backwardPort, &GPIO_InitStruct);
    HAL_GPIO_WritePin(backwardPort, backwardPin, GPIO_PIN_RESET);

}

void Wheel::GoForward(float ratio)
{
    HAL_GPIO_WritePin(_forwardPort,_forwardPin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(_backwardPort, _backwardPin, GPIO_PIN_RESET);
}
void Wheel::GoBack( float ratio)
{
    HAL_GPIO_WritePin(_backwardPort,_backwardPin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(_forwardPort, _forwardPin, GPIO_PIN_RESET);
}
void Wheel::Stop()
{
    HAL_GPIO_WritePin(_backwardPort, _backwardPin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_forwardPort, _forwardPin, GPIO_PIN_RESET);
}
