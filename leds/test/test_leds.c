#include "unity.h"
#include <stdint.h>
#include "leds.h"

static uint16_t puerto_virtual;

void setUp(void)
{
    leds_init(&puerto_virtual);
}

//Al inicializar la biblioteca todos los leds deben quedar apagados
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t puerto_virtual = 0xFFFF;
    leds_init(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

//Con todos los leds apagados, prendo el led 2, verifico que el bit 1 vale 1
void test_prender_un_led(void)
{
    leds_turn_on_single(2);
    TEST_ASSERT_EQUAL_HEX16(0x0002, puerto_virtual);
}

//Con el led 2 prendido, apago el led 2, verifico que el bit 1 vale 0
void test_prender_y_apagar_un_led(void)
{
    leds_turn_on_single(2);
    leds_turn_off_single(2);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

//Con todos los leds apagados, prendo el 3, prendo el 5, apago el 3 y apago el 7, deberían quedar el bit 4 en 1 y el resto en 0
void test_prender_y_apagar_varios_leds(void)
{
    leds_turn_on_single(3);
    leds_turn_on_single(5);
    leds_turn_off_single(3);
    leds_turn_off_single(7);
    TEST_ASSERT_EQUAL_HEX16(0x0010, puerto_virtual);
}

//Prendo un led, consulto el estado y tiene que estar prendido
void test_preder_un_led_y_consultar_estado(void)
{
    leds_turn_on_single(2);
    TEST_ASSERT_TRUE(leds_is_turned_on(2));
}

//Apago un led, consulto el estado y tiene que estar apagado
void test_apagar_un_led_y_consultar_estado(void)
{
    //Al inicializar el puerto todos los leds quedan apagados
    //Por lo tanto solamente basta con verificar que un led cualquiera está apagado
    TEST_ASSERT_FALSE(leds_is_turned_on(2));
}

//Con todos los leds apagados, enciendo todos los leds y verifico que se encienden
void test_prender_todos_los_leds_y_consultar_estado(void)
{
    leds_turn_on_all();
    TEST_ASSERT_TRUE(leds_all_turned_on());
}

//Con todos los leds encendidos, apago todos los leds y verifico que se apagan
void test_apagar_todos_los_leds_y_consultar_estado(void)
{
    leds_turn_on_all();
    leds_turn_off_all();
    TEST_ASSERT_FALSE(leds_all_turned_on());
}