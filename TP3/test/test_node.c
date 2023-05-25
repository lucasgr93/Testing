#include "unity.h"
#include "node.h"


static node_t node;

void setUp(void)
{
    node = node_create(1);
}

void teardown(void)
{
    node_delete(node);
}

//Crear un nodo con dirección 1 y verificar que no devuelva NULL
void test_create_one_node_with_correct_address_and_verify_that_it_is_not_null(void)
{
    node_t node = node_create(1);
    TEST_ASSERT_NOT_NULL(node);
}

//Crear un nodo con dirección 0 y verificar que devuelva NULL
void test_create_one_node_with_wrong_address(void)
{
    node_t node = node_create(0);
    TEST_ASSERT_NULL(node);
}

//Eliminar un nodo y verificar que devuelva NULL
void test_delete_one_node_and_verify_that_the_memory_has_been_released(void)
{
    node = node_delete(node);
    TEST_ASSERT_NULL(node);

}

//Crear un nodo con dirección 1 y solicitar la dirección. Esta debe ser igual a 1
void test_create_one_node_and_get_its_address(void)
{
    node_t node = node_create(1);
    TEST_ASSERT_EQUAL_INT8(1, node_get_mb_address(node));
}

//Cambiar la dirección de un nodo y verificar que haya cambiado
void test_change_node_address(void)
{
    node_set_mb_address(node, 2);
    TEST_ASSERT_EQUAL_INT8(2, node_get_mb_address(node));
}

//Verificar que la cantidad de parámetros de un nodo sea igual a 4
void test_get_node_parameters_count(void)
{
    TEST_ASSERT_EQUAL(4, node_get_mb_params_count(node));
}

//Solicitar el parámetro 2 del nodo y verificar que no sea nulo
void test_get_node_parameters_list(void)
{
    mb_parameter_descriptor_t* params = NULL;
    params = node_get_mb_descriptor(node, 3);
    TEST_ASSERT_NOT_NULL(params);
}



