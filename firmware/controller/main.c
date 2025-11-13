#include "stm32f1xx.h"

void delay_ms(uint16_t ms)
{
    TIM2->PSC = 8000 - 1; // 8 000 000 Hz / 8 000 = 1 000 Hz (1 ms)
    TIM2->ARR = ms - 1;   // desired delay
    TIM2->CR1 |= TIM_CR1_CEN;
    while (!(TIM2->SR & TIM_SR_UIF))
    {
    }                          // wait UIF to be set
    TIM2->SR &= ~TIM_SR_UIF;   // reset UIF
    TIM2->CR1 &= ~TIM_CR1_CEN; // Disable the timer
}

int main(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;

    GPIOC->CRH &= ~GPIO_CRH_CNF13_Msk;
    GPIOC->CRH |= (GPIO_CRH_MODE13_0);
    
    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_ODR13;
        delay_ms(500);
    }
}