#include "unity.h"
#include <stdint.h>
#include "leds.h"

//Al inicializar la biblioteca todos los leds deben quedar apagados
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t puerto_virtual = 0xFFFF;
    leds_init(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}