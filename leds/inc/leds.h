#ifndef _LEDS_H_
#define _LEDS_H_

#include <stdint.h>

void leds_init(uint16_t* direccion);

void leds_turn_on_single(uint8_t led);

void leds_turn_off_single(uint8_t led);

#endif