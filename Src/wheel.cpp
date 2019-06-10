#include "wheel.h"
void Wheel::GoForward( uint16_t duration)
{
    HAL_GPIO_WritePin(_forwardPort,_forwardPin,GPIO_PIN_SET);
    HAL_Delay(duration);

    HAL_GPIO_WritePin(_forwardPort,_forwardPin,GPIO_PIN_RESET);
}
