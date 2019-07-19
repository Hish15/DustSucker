#pragma once 
extern "C" 
{

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
}
class Wheel
{
    public:
        
        Wheel(TIM_HandleTypeDef *tim, uint32_t forwardChannel, uint32_t backwardChannel); 
        /*
         * Turn the wheel forward at given pwm ratio
         *
         * \param ratio [0 : 1.0] pwm ratio
         */
        void GoForward();
        /*
         * Turn the wheel backward at given pwm ratio
         *
         * \param ratio [0 : 1.0] pwm ratio
         */
        void GoBack();
        /*
         * Stop any wheel motion 
         */
        void Stop();

    private:
        TIM_HandleTypeDef *_TIM_Handle;
        uint32_t _farwardChannel;
        uint32_t _backwardChannel;
};
