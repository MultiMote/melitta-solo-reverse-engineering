#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_utils.h"
#include "config.h"

/** GPIOC */
#define LED_PIN             LL_GPIO_PIN_13
/** GPIOA */
#define POWER_ENABLE_PIN    LL_GPIO_PIN_0
#define MOTOR_FWD_PIN       LL_GPIO_PIN_2
#define MOTOR_REV_PIN       LL_GPIO_PIN_3

enum motor_value
{
    MOTOR_OFF = 0,
    MOTOR_FWD = 1,
    MOTOR_REV = 2
};

void GPIO_Config(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

    LL_GPIO_InitTypeDef led = {0};
    led.Pin = LL_GPIO_PIN_13;
    led.Mode = LL_GPIO_MODE_OUTPUT;
    led.Speed = LL_GPIO_SPEED_FREQ_LOW;
    led.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOC, &led);

    LL_GPIO_InitTypeDef out_pulldown = {0};
    out_pulldown.Pin = POWER_ENABLE_PIN | MOTOR_FWD_PIN | MOTOR_REV_PIN;
    out_pulldown.Mode = LL_GPIO_MODE_OUTPUT;
    out_pulldown.Speed = LL_GPIO_SPEED_FREQ_LOW;
    out_pulldown.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    out_pulldown.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(GPIOA, &out_pulldown);
}

void SystemClock_Config(void)
{
    LL_Init1msTick(8000000);
    LL_SetSystemCoreClock(8000000);
}

void power_enable(uint8_t on)
{
    if (on)
    {
        LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
    }
    else
    {
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
    }
}

void motor_set(enum motor_value value)
{
    switch (value)
    {

    case MOTOR_OFF:
        LL_GPIO_ResetOutputPin(GPIOA, MOTOR_FWD_PIN | MOTOR_REV_PIN);
        break;

    case MOTOR_FWD:
        LL_GPIO_ResetOutputPin(GPIOA, MOTOR_REV_PIN);
        LL_GPIO_SetOutputPin(GPIOA, MOTOR_FWD_PIN);
        break;

    case MOTOR_REV:
        LL_GPIO_ResetOutputPin(GPIOA, MOTOR_FWD_PIN);
        LL_GPIO_SetOutputPin(GPIOA, MOTOR_REV_PIN);
        break;
    }
}

int main(void)
{
    SystemClock_Config();
    GPIO_Config();

    power_enable(1);

    LL_GPIO_SetOutputPin(GPIOC, LED_PIN);


    motor_set(MOTOR_FWD);
    LL_mDelay(500);
    motor_set(MOTOR_REV);
    LL_mDelay(500);
    motor_set(MOTOR_OFF);

    LL_mDelay(1000);

    power_enable(0);


    while (1)
    {
        // LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        // LL_mDelay(500);
    }
}
