#pragma once 
extern "C" 
{

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
}
class Wheel
{
    public:
        Wheel(GPIO_TypeDef* forwardPort, uint16_t forwardPin, GPIO_TypeDef* backwardPort, uint16_t backwardPin):
            _forwardPort(forwardPort), _forwardPin(forwardPin), _backwardPort(backwardPort), _backwardPin(backwardPin){}

        void GoForward(uint16_t duration_ms);
    private:
        GPIO_TypeDef* _forwardPort;
        uint16_t _forwardPin;
        GPIO_TypeDef* _backwardPort;
        uint16_t _backwardPin;
};
