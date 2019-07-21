#include "wheel.h"

Wheel::Wheel(TIM_HandleTypeDef *tim, uint32_t forwardChannel, uint32_t backwardChannel) 
{

    _TIM_Handle = tim;
    _farwardChannel = forwardChannel;
    _backwardChannel = backwardChannel;
}

void Wheel::SetPWMRatio(uint32_t channel, float ratio)
{
    if(ratio > 1.0f)
    {
        ratio = 1.0f;
    }
    else if(ratio < 0.0f)
    {
        ratio = 0.0f;
    }
    uint16_t period = static_cast<uint16_t>(ratio * _TIM_Handle->Init.Period);  
    switch(channel)
    {
        case TIM_CHANNEL_1:
            _TIM_Handle->Instance->CCR1 = period;
            break;
        case TIM_CHANNEL_2:
            _TIM_Handle->Instance->CCR2 = period;
            break;
        case TIM_CHANNEL_3:
            _TIM_Handle->Instance->CCR3 = period;
            break;
        case TIM_CHANNEL_4:
            _TIM_Handle->Instance->CCR4 = period;
            break;
    }
}


void Wheel::GoForward(float ratio)
{
    SetPWMRatio(_farwardChannel, ratio);
    HAL_TIM_PWM_Stop(_TIM_Handle, _backwardChannel);
    HAL_TIM_PWM_Start(_TIM_Handle, _farwardChannel);
}

void Wheel::GoBack(float ratio)
{
    SetPWMRatio(_backwardChannel, ratio);
    HAL_TIM_PWM_Stop(_TIM_Handle, _farwardChannel);
    HAL_TIM_PWM_Start(_TIM_Handle, _backwardChannel);
}

void Wheel::Stop()
{
    HAL_TIM_PWM_Stop(_TIM_Handle, _backwardChannel);
    HAL_TIM_PWM_Stop(_TIM_Handle, _farwardChannel);
}
