#ifndef _ESP_MB_MASTER_INTERFACE_H
#define _ESP_MB_MASTER_INTERFACE_H

#include <stdint.h>

#define BIT2     0x00000004
#define BIT1     0x00000002
#define BIT0     0x00000001

/**
 * @brief Type of Modbus parameter
 */
typedef enum {
    MB_PARAM_HOLDING = 0x00,         /*!< Modbus Holding register. */
    MB_PARAM_INPUT,                  /*!< Modbus Input register. */
    MB_PARAM_COIL,                   /*!< Modbus Coils. */
    MB_PARAM_DISCRETE,               /*!< Modbus Discrete bits. */
    MB_PARAM_COUNT,
    MB_PARAM_UNKNOWN = 0xFF
} mb_param_type_t;


/*!
 * \brief Modbus descriptor table parameter type defines.
 */
typedef enum {
    PARAM_TYPE_U8 = 0x00,                   /*!< Unsigned 8 */
    PARAM_TYPE_U16 = 0x01,                  /*!< Unsigned 16 */
    PARAM_TYPE_U32 = 0x02,                  /*!< Unsigned 32 */
    PARAM_TYPE_FLOAT = 0x03,                /*!< Float type */
    PARAM_TYPE_ASCII = 0x04                 /*!< ASCII type */
} mb_descr_type_t;

/*!
 * \brief Modbus descriptor table parameter size in bytes.
 */
typedef enum {
    PARAM_SIZE_U8 = 0x01,                   /*!< Unsigned 8 */
    PARAM_SIZE_U16 = 0x02,                  /*!< Unsigned 16 */
    PARAM_SIZE_U32 = 0x04,                  /*!< Unsigned 32 */
    PARAM_SIZE_FLOAT = 0x04,                /*!< Float size */
    PARAM_SIZE_ASCII = 0x08,                /*!< ASCII size */
    PARAM_SIZE_ASCII24 = 0x18,              /*!< ASCII24 size */
    PARAM_MAX_SIZE
} mb_descr_size_t;

/*!
 * \brief Modbus parameter options for description table
 */
typedef union {
    struct {
        int opt1;                         /*!< Parameter option1 */
        int opt2;                         /*!< Parameter option2 */
        int opt3;                         /*!< Parameter option3 */
    };
    struct {
        int min;                          /*!< Parameter minimum value */
        int max;                          /*!< Parameter maximum value */
        int step;                         /*!< Step of parameter change tracking */
    };
} mb_parameter_opt_t;

/**
 * @brief Permissions for the characteristics
 */
typedef enum {
    PAR_PERMS_READ               = 1 << BIT0,                                   /**< the characteristic of the device are readable */
    PAR_PERMS_WRITE              = 1 << BIT1,                                   /**< the characteristic of the device are writable*/
    PAR_PERMS_TRIGGER            = 1 << BIT2,                                   /**< the characteristic of the device are triggerable */
    PAR_PERMS_READ_WRITE         = PAR_PERMS_READ | PAR_PERMS_WRITE,            /**< the characteristic of the device are readable & writable */
    PAR_PERMS_READ_TRIGGER       = PAR_PERMS_READ | PAR_PERMS_TRIGGER,          /**< the characteristic of the device are readable & triggerable */
    PAR_PERMS_WRITE_TRIGGER      = PAR_PERMS_WRITE | PAR_PERMS_TRIGGER,         /**< the characteristic of the device are writable & triggerable */
    PAR_PERMS_READ_WRITE_TRIGGER = PAR_PERMS_READ_WRITE | PAR_PERMS_TRIGGER,    /**< the characteristic of the device are readable & writable & triggerable */
} mb_param_perms_t;

/**
 * @brief Characteristics descriptor type is used to describe characteristic and
 * link it with Modbus parameters that reflect its data.
 */
typedef struct {
    uint16_t            cid;                /*!< Characteristic cid */
    const char*         param_key;          /*!< The key (name) of the parameter */
    const char*         param_units;        /*!< The physical units of the parameter */
    uint8_t             mb_slave_addr;      /*!< Slave address of device in the Modbus segment */
    mb_param_type_t     mb_param_type;      /*!< Type of modbus parameter */
    uint16_t            mb_reg_start;       /*!< This is the Modbus register address. This is the 0 based value. */
    uint16_t            mb_size;            /*!< Size of mb parameter in registers */
    uint16_t            param_offset;       /*!< Parameter name (OFFSET in the parameter structure) */
    mb_descr_type_t     param_type;         /*!< Float, U8, U16, U32, ASCII, etc. */
    mb_descr_size_t     param_size;         /*!< Number of bytes in the parameter. */
    mb_parameter_opt_t  param_opts;         /*!< Parameter options used to check limits and etc. */
    mb_param_perms_t    access;             /*!< Access permissions based on mode */
} mb_parameter_descriptor_t;

#endif