#include "wheel.h"

Wheel::Wheel(TIM_HandleTypeDef *tim, uint32_t forwardChannel, uint32_t backwardChannel) 
{

    _TIM_Handle = tim;
    _farwardChannel = forwardChannel;
    _backwardChannel = backwardChannel;
}

void Wheel::GoForward()
{

    HAL_TIM_PWM_Stop(_TIM_Handle, _backwardChannel);
    HAL_TIM_PWM_Start(_TIM_Handle, _farwardChannel);
}
void Wheel::GoBack()
{
    HAL_TIM_PWM_Stop(_TIM_Handle, _farwardChannel);
    HAL_TIM_PWM_Start(_TIM_Handle, _backwardChannel);
        
}
void Wheel::Stop()
{
    
    HAL_TIM_PWM_Stop(_TIM_Handle, _backwardChannel);
    HAL_TIM_PWM_Stop(_TIM_Handle, _farwardChannel);
}
