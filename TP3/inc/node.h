#ifndef _NODE_H_
#define _NODE_H_

#include <stdint.h>
#include <stdbool.h>
#include "mbcontroller.h"

#define BI1_PORT_CID	0 //Discrete input port 1 caracteristic ID
#define BO1_PORT_CID	1 //Coils port 1 caracteristic ID
#define	HR1_PORT_CID	2 //Holding register 1 caracteristic ID
#define HR2_PORT_CID	3 //Holding register 2 caracteristic ID

typedef struct node_s *node_t;

typedef enum
{
	NODE_ERR = -1,
	NODE_OK = 0,
}node_err_t;


node_t node_create(uint8_t address);

node_t node_delete(node_t node);

uint8_t node_get_mb_address(node_t node);

bool node_set_mb_address(node_t node, uint8_t new_address);

uint8_t node_get_mb_params_count(node_t node);

mb_parameter_descriptor_t* node_get_mb_descriptor(node_t node, uint8_t cid);

bool node_is_connected(node_t node);

uint8_t* node_mb_discrete_inputs(node_t node);

uint8_t* node_mb_coils(node_t node);

uint16_t* node_mb_input_regs(node_t node);

uint16_t* node_mb_holding_regs(node_t node);

#endif
