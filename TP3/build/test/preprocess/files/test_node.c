#include "inc/node.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




static node_t node;



void setUp(void)

{

    node = node_create(1);

}



void teardown(void)

{

    node_delete(node);

}





void test_create_one_node_with_correct_address_and_verify_that_it_is_not_null(void)

{

    node_t node = node_create(1);

    do {if ((((node)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(21))));}} while(0);

}





void test_create_one_node_with_wrong_address(void)

{

    node_t node = node_create(0);

    do {if ((((node)) == 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(28))));}} while(0);

}





void test_delete_one_node_and_verify_that_the_memory_has_been_released(void)

{

    node = node_delete(node);

    do {if ((((node)) == 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(35))));}} while(0);



}





void test_create_one_node_and_get_its_address(void)

{

    node_t node = node_create(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((1)), (UNITY_INT)(UNITY_INT8 )((node_get_mb_address(node))), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT8);

}





void test_change_node_address(void)

{

    node_set_mb_address(node, 2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((2)), (UNITY_INT)(UNITY_INT8 )((node_get_mb_address(node))), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT8);

}





void test_get_node_parameters_count(void)

{

    UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((node_get_mb_params_count(node))), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

}





void test_get_node_parameters_list(void)

{

    mb_parameter_descriptor_t* params = 

                                       ((void *)0)

                                           ;

    params = node_get_mb_descriptor(node, 3);

    do {if ((((params)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(64))));}} while(0);

}
