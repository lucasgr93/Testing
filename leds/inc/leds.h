#ifndef _LEDS_H_
#define _LEDS_H_

#include <stdint.h>
#include <stdbool.h>

void leds_init(uint16_t* direccion);

void leds_turn_on_single(uint8_t led);

void leds_turn_off_single(uint8_t led);

bool leds_is_turned_on(uint8_t led);

void leds_turn_on_all();

void leds_turn_off_all();

bool leds_all_turned_on();

#endif