#include "leds.h"

#define INDEX_OFFSET 1
#define FIRST_BIT 1
#define ALL_LEDS_OFF 0x0000

static uint16_t* puerto;

uint16_t index_to_mask(uint8_t led)
{
    return (FIRST_BIT << (led-INDEX_OFFSET));
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