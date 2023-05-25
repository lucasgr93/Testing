#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define BI_COUNT	1	//Discrete inputs ports count (8 bits, read-write)
#define BO_COUNT	1	//Coils ports count (8 bits, read-write)
#define IR_COUNT	1	//Input registers count (16 bits, read-only)
#define HR_COUNT	2	//Holding registers count (16 bits, read-write)

typedef struct
{
	char date[10]; // "dd/MM/yy"
	char hour[10]; // "hh:mm:ss"
	uint8_t binary_inputs[BI_COUNT];
	uint8_t binary_outputs[BO_COUNT];
	uint16_t analog_inputs[HR_COUNT];
} node_data_t;

struct node_s
{
	bool connected;
	uint8_t address;
	uint8_t node_params_count;
	node_data_t last_data;
	mb_parameter_descriptor_t* mb_cid_list;
};

mb_parameter_descriptor_t node_parameters[] =
{
	{
		.cid 			= BI1_PORT_CID,
		.param_key 		= "Digital Inputs",
		.param_units 	= "",
		.mb_slave_addr 	= 0,
		.mb_param_type 	= MB_PARAM_DISCRETE,
		.mb_reg_start 	= 0,
		.mb_size 		= 1,
		.param_offset 	= 1,
		.param_type 	= PARAM_TYPE_U8,
		.param_size 	= PARAM_SIZE_U8,
		.param_opts		= {.opt1=0, .opt2=0, .opt3=0},
		.access 		= PAR_PERMS_READ_TRIGGER
	},
	{
		.cid 			= BO1_PORT_CID,
		.param_key 		= "Digital Outputs",
		.param_units 	= "",
		.mb_slave_addr 	= 0,
		.mb_param_type 	= MB_PARAM_COIL,
		.mb_reg_start 	= 0,
		.mb_size 		= 1,
		.param_offset 	= 1,
		.param_type 	= PARAM_TYPE_U8,
		.param_size 	= PARAM_SIZE_U8,
		.param_opts		= {.opt1=0, .opt2=0, .opt3=0},
		.access 		= PAR_PERMS_READ_WRITE_TRIGGER
	},
	{
		.cid 			= HR1_PORT_CID,
		.param_key 		= "Voltage",
		.param_units 	= "V",
		.mb_slave_addr 	= 0,
		.mb_param_type 	= MB_PARAM_HOLDING,
		.mb_reg_start 	= 0,
		.mb_size 		= 2,
		.param_offset 	= 1,
		.param_type 	= PARAM_TYPE_U16,
		.param_size 	= PARAM_SIZE_U16,
		.param_opts		= {.opt1=0, .opt2=250, .opt3=1},
		.access 		= PAR_PERMS_READ_TRIGGER
	},
	{
		.cid 			= HR2_PORT_CID,
		.param_key 		= "Current",
		.param_units 	= "A",
		.mb_slave_addr 	= 0,
		.mb_param_type 	= MB_PARAM_HOLDING,
		.mb_reg_start 	= 0,
		.mb_size 		= 2,
		.param_offset 	= 2,
		.param_type 	= PARAM_TYPE_U16,
		.param_size 	= PARAM_SIZE_U16,
		.param_opts		= {.opt1=0, .opt2=100, .opt3=1},
		.access 		= PAR_PERMS_READ_TRIGGER
	}

};

const uint16_t num_node_parameters = (sizeof(node_parameters) / sizeof(mb_parameter_descriptor_t));

node_t node_create(uint8_t address)
{
	node_t node = malloc(sizeof(struct node_s));
	if(node != NULL)
	{
		node->mb_cid_list = malloc(num_node_parameters * sizeof(mb_parameter_descriptor_t));
		if(NULL == node->mb_cid_list)
		{
			printf("Error: No se pudo reservar memoria para almacenar los parámetros\n\r");
			node_delete(node);
			return node;
		}
		node->node_params_count = num_node_parameters;
		memcpy(node->mb_cid_list, node_parameters, sizeof(node_parameters));
		memset(&node->last_data, 0, sizeof(node->last_data));
		if(false == node_set_mb_address(node, address))
		{
			printf("Error: No se pudo setear la dirección del nodo\n\r");
			node = node_delete(node);
			return node;
		}
		node->connected = false;
		printf("Nodo almacenado en la dirección de memoria: %p\n\r", node);
	}
	return node;
}

node_t node_delete(node_t node)
{
	free(node->mb_cid_list);
	free(node);
	return NULL;
}

uint8_t node_get_mb_address(node_t node)
{
	if(node != NULL)
	{
		return node->address;
	}
	else return 0;
}

bool node_set_mb_address(node_t node, uint8_t new_address)
{
	if(node != NULL && new_address != 0)
	{
		for(int i=0; i<node_get_mb_params_count(node); i++)
		{
			node->mb_cid_list->mb_slave_addr = new_address;
		}
		node->address = new_address;
		return true;
	}
	else return false;
}

uint8_t node_get_mb_params_count(node_t node)
{
	return node->node_params_count;
}

mb_parameter_descriptor_t* node_get_mb_descriptor(node_t node, uint8_t cid)
{
	if(cid < node_get_mb_params_count(node))
	{
		mb_parameter_descriptor_t* param = &node->mb_cid_list[cid];
		return param;
	}
	else return NULL;
}

bool node_is_connected(node_t node)
{
	if(node != NULL)
	{
		return node->connected;
	}
	else return false;
}

uint8_t* node_mb_discrete_inputs(node_t node)
{
	return node->last_data.binary_inputs;
}

uint8_t* node_mb_coils(node_t node)
{
	return node->last_data.binary_outputs;
}

uint16_t* node_mb_input_regs(node_t node)
{
	return NULL;
}

uint16_t* node_mb_holding_regs(node_t node)
{
	return node->last_data.analog_inputs;
}
