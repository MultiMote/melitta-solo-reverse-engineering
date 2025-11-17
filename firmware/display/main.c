#include <avr/io.h>
#include <util/delay.h>

#define LED1_PIN PD5
#define LED2_PIN PD4
#define LED3_PIN PD3
#define LED4_PIN PD2
#define LED5_PIN PC3
#define LED6_PIN PC2
#define LED7_PIN PC1
#define LED8_PIN PC0
#define LED9_PIN PD7
#define LED10_PIN PD6

void set_led_by_index(uint8_t index, uint8_t value)
{
    if (index == 0)
    {
        if (value)
            PORTD |= (1 << LED1_PIN);
        else
            PORTD &= ~(1 << LED1_PIN);
    }
    else if (index == 1)
    {
        if (value)
            PORTD |= (1 << LED2_PIN);
        else
            PORTD &= ~(1 << LED2_PIN);
    }
    else if (index == 2)
    {
        if (value)
            PORTD |= (1 << LED3_PIN);
        else
            PORTD &= ~(1 << LED3_PIN);
    }
    else if (index == 3)
    {
        if (value)
            PORTD |= (1 << LED4_PIN);
        else
            PORTD &= ~(1 << LED4_PIN);
    }
    else if (index == 4)
    {
        if (value)
            PORTC |= (1 << LED5_PIN);
        else
            PORTC &= ~(1 << LED5_PIN);
    }
    else if (index == 5)
    {
        if (value)
            PORTC |= (1 << LED6_PIN);
        else
            PORTC &= ~(1 << LED6_PIN);
    }
    else if (index == 6)
    {
        if (value)
            PORTC |= (1 << LED7_PIN);
        else
            PORTC &= ~(1 << LED7_PIN);
    }
    else if (index == 7)
    {
        if (value)
            PORTC |= (1 << LED8_PIN);
        else
            PORTC &= ~(1 << LED8_PIN);
    }
    else if (index == 8)
    {
        if (value)
            PORTD |= (1 << LED9_PIN);
        else
            PORTD &= ~(1 << LED9_PIN);
    }
    else if (index == 9)
    {
        if (value)
            PORTD |= (1 << LED10_PIN);
        else
            PORTD &= ~(1 << LED10_PIN);
    }
}

int main()
{
    DDRD = 0xFF;
    DDRC = 0xFF;

    while (1)
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            PORTD = 0x00;
            PORTC = 0x00;
            set_led_by_index(i, 1);
            _delay_ms(50);
        }

        for (uint8_t i = 0; i < 10; i++)
        {
            PORTD = 0x00;
            PORTC = 0x00;
            set_led_by_index(9 - i, 1);
            _delay_ms(50);
        }
    }
}
