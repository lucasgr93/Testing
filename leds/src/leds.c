#include "leds.h"

#define INDEX_OFFSET    1
#define FIRST_BIT       1
#define ALL_LEDS_OFF    0x0000
#define ALL_LEDS_ON     0xFFFF

static uint16_t* puerto;

uint16_t index_to_mask(uint8_t led)
{
    uint16_t retval = FIRST_BIT << (led-INDEX_OFFSET);
    return (retval);
}

void leds_init(uint16_t* direccion)
{
    puerto = direccion;
    *direccion = ALL_LEDS_OFF;
}

void leds_turn_on_single(uint8_t led)
{
    *puerto |= index_to_mask(led);
}

void leds_turn_off_single(uint8_t led)
{
    *puerto &= ~index_to_mask(led);
}

bool leds_is_turned_on(uint8_t led)
{
    uint16_t masked_port_value = *puerto & index_to_mask(led);
    return (masked_port_value != ALL_LEDS_OFF);
}

void leds_turn_on_all()
{
    *puerto = ALL_LEDS_ON;
}

void leds_turn_off_all()
{
    *puerto = ALL_LEDS_OFF;
}

bool leds_all_turned_on()
{
    return (*puerto == ALL_LEDS_ON);
}