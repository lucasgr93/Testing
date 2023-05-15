#include "inc/leds.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




static uint16_t puerto_virtual;



void setUp(void)

{

    leds_init(&puerto_virtual);

}





void test_todos_los_leds_inician_apagados(void)

{

    uint16_t puerto_virtual = 0xFFFF;

    leds_init(&puerto_virtual);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_un_led(void)

{

    leds_turn_on_single(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0002)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_un_led(void)

{

    leds_turn_on_single(2);

    leds_turn_off_single(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_varios_leds(void)

{

    leds_turn_on_single(3);

    leds_turn_on_single(5);

    leds_turn_off_single(3);

    leds_turn_off_single(7);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0010)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_HEX16);

}





void test_preder_un_led_y_consultar_estado(void)

{

    

   _Bool 

        led_turned_on = 

                        0

                             ;

    leds_turn_on_single(2);

    led_turned_on = leds_is_turned_on(2);

    do {if ((led_turned_on)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(51)));}} while(0);

}





void test_apagar_un_led_y_consultar_estado(void)

{

    

   _Bool 

        led_turned_on = 

                        1

                            ;

    leds_turn_on_single(2);

    leds_turn_off_single(2);

    led_turned_on = leds_is_turned_on(2);

    do {if (!(led_turned_on)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(61)));}} while(0);

}





void test_prender_todos_los_leds_y_consultar_estado(void)

{

    

   _Bool 

        all_leds_turned_on = 

                             0

                                  ;

    leds_turn_on_all();

    all_leds_turned_on = leds_all_turned_on();

    do {if ((all_leds_turned_on)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(70)));}} while(0);

}





void test_apagar_todos_los_leds_y_consultar_estado(void)

{

    

   _Bool 

        all_leds_turned_on = 

                             1

                                 ;

    leds_turn_on_all();

    leds_turn_off_all();

    all_leds_turned_on = leds_all_turned_on();

    do {if (!(all_leds_turned_on)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

}
