#pragma once 
extern "C" 
{

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
}
class Wheel
{
    public:
        Wheel(GPIO_TypeDef* forwardPort, uint16_t forwardPin, GPIO_TypeDef* backwardPort, uint16_t backwardPin);

        /*
         * Turn the wheel forward at given pwm ratio
         *
         * \param ratio [0 : 1.0] pwm ratio
         */
        void GoForward(float ratio = 1.0f);
        /*
         * Turn the wheel backward at given pwm ratio
         *
         * \param ratio [0 : 1.0] pwm ratio
         */
        void GoBack(float ratio = 1.0f);
        /*
         * Stop any wheel motion 
         */
        void Stop();

    private:
        GPIO_TypeDef* _forwardPort;
        uint16_t _forwardPin;
        GPIO_TypeDef* _backwardPort;
        uint16_t _backwardPin;
};
