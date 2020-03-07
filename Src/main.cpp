/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "string.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "wheel.h"
#include "tim.h"
#include "i2c.h"

#include "vl53l1_api.h"
#include "vl53l1_platform.h"
#include "MPU9250_Master_I2C_STM32_HAL.h"
/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

extern "C" { 
    void delay(uint32_t msec)
    {
        HAL_Delay(msec);
    }
}
/* Private variables ---------------------------------------------------------*/
/*
 * 'S' stop
 * 'F'orward
 * 'B'ackward
 * 'L'eft
 * 'R'ight
 */
char motorsAction = 'S';


const uint32_t DIAGNOSTIC_START_DELAY_MS =  5000;

Wheel wheel1(&htim4, TIM_CHANNEL_1, TIM_CHANNEL_2); 
Wheel wheel2(&htim4, TIM_CHANNEL_3, TIM_CHANNEL_4); 
constexpr int32_t blinkPeriodMs = 100;
constexpr int32_t holdButtonMS = 250;
uint8_t byteData = 0;
VL53L1_Dev_t                   dev;
VL53L1_DEV                     Dev = &dev;
/*
Gscale: GFS_250 = 250 dps, GFS_500 = 500 dps, GFS_1000 = 1000 dps, GFS_2000DPS = 2000 degrees per second gyro full scale
Ascale: AFS_2G = 2 g, AFS_4G = 4 g, AFS_8G = 8 g, and AFS_16G = 16 g accelerometer full scale
Mscale: MFS_14BITS = 0.6 mG per LSB and MFS_16BITS = 0.15 mG per LSB
Mmode:  Mmode = M_8Hz for 8 Hz data rate or Mmode = M_100Hz for 100 Hz data rate
SAMPLE_RATE_DIVISOR: (1 + SAMPLE_RATE_DIVISOR) is a simple divisor of the fundamental 1000 kHz rate of the gyro and accel, so 
SAMPLE_RATE_DIVISOR = 0x00 means 1 kHz sample rate for both accel and gyro, 0x04 means 200 Hz, etc.
 */
 static const MPUIMU::Ascale_t  ASCALE              = MPUIMU::AFS_2G;
 static const MPUIMU::Gscale_t  GSCALE              = MPUIMU::GFS_250DPS;
 static const MPU9250::Mscale_t MSCALE              = MPU9250::MFS_16BITS;
 static const MPU9250::Mmode_t  MMODE               = MPU9250::M_100Hz;
 static const uint8_t           SAMPLE_RATE_DIVISOR = 4;   
MPU9250_Master_I2C_STM32_HAL imu(ASCALE, GSCALE, MSCALE, MMODE, &hi2c2, SAMPLE_RATE_DIVISOR);
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void usbRxCallback(uint8_t *buffer, uint32_t len)
{
    printf("Motor action : %c", motorsAction);
    if(len > 0)
    {
        motorsAction = buffer[0];
        printf("Motor action : %c\n", motorsAction);
    } 

}
void Init(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_TIM4_Init(); 
    MX_USB_DEVICE_Init_User(&usbRxCallback);
    MX_I2C1_Init();
    MX_I2C2_Init();


    //Enable H bridge motors
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

}
bool Diagnostic(void)
{
    bool isDiagnosticOK = true;
    printf("Starting wheels test\n");
    wheel1.GoForward();
    HAL_Delay(500);
    wheel1.GoBack();
    HAL_Delay(500);
    wheel1.Stop();

    HAL_Delay(1000);
    wheel2.GoForward();
    HAL_Delay(500);
    wheel2.GoBack();
    HAL_Delay(500);
    wheel2.Stop();
    //Enabling ToF sensor VL53L1
	printf("Starting ToF sensor test\n");
    Dev->I2cHandle = &hi2c1;
    Dev->I2cDevAddr = 0x52;  
    VL53L1_RdByte(Dev, VL53L1_IDENTIFICATION__MODEL_ID, &byteData);

    printf("VL53L1X Model_ID: %02X\n", byteData);
    if(byteData != 0xEA)
    {
        isDiagnosticOK = false;
        printf("ErrorT on Tof sensor init\n");
	}
    
    printf("Starting the MPU9250 device\n");
    switch (imu.begin()) {

        case MPUIMU::ERROR_IMU_ID:
            printf("Bad IMU device ID\n");
            break;
        case MPUIMU::ERROR_MAG_ID:
            printf("Bad magnetometer device ID\n");
            break;
        case MPUIMU::ERROR_SELFTEST:
            //error("Failed self-test");
            break;
        default:
            printf("MPU9250 init!\n");
    }
    return isDiagnosticOK;
}

void StepLoop(void)
{
    uint32_t timeNow = HAL_GetTick();

    //Handling the LED status blink
    static uint32_t lastBlink = HAL_GetTick();
    if( timeNow - lastBlink > blinkPeriodMs)
    {
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        lastBlink = timeNow;
    }

    //Handling the user button action : toggle back and forth motion
    static uint32_t lastButtonRelease = HAL_GetTick();
    if(GPIO_PIN_SET == HAL_GPIO_ReadPin(USER_Btn_GPIO_Port,USER_Btn_Pin))
    {
        if(timeNow - lastButtonRelease > holdButtonMS)
        {
            motorsAction = (motorsAction != 'F')? 'F' : 'B';
            lastButtonRelease = timeNow;
        }
    }
    else
    {
        lastButtonRelease = timeNow;
    }

    //Handling the motor motion
    static char lastMotorAction = '0';
    if(lastMotorAction != motorsAction)
    {
        switch(motorsAction)
        {
            case 'L':
                wheel1.GoForward();
                wheel2.Stop();

                break;
            case 'R':
                wheel1.Stop();
                wheel2.GoForward();
                break;
            case 'B':
                wheel1.GoBack();
                wheel2.GoBack();
                break;
            case 'F':
                wheel1.GoForward();
                wheel2.GoForward();
                break;
            case 'S':
            default:
                wheel1.Stop();
                wheel2.Stop();
                break;
        } 
    }
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    Init();
    HAL_Delay(DIAGNOSTIC_START_DELAY_MS);
    if(Diagnostic() == false)
    {
        printf("Error on Diagnostic\n");
    }
    /* Infinite loop */
    printf("Entering main loop\n");
    while (1)
    {
        StepLoop();
    }
}

extern "C"
{
    int _write(int file, char *ptr, int len) 
    {
        CDC_Transmit_FS((uint8_t*)ptr, len);

        return len;
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
