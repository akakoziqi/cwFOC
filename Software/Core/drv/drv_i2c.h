#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include "sys_inc.h"

typedef struct tagI2CInstance
{
    void *__u__nused;
} *I2CInstance;

extern const I2CInstance I2C_Instance1;
extern const I2CInstance I2C_Instance2;

extern void drv_i2c_init(void);
extern void drv_i2c_write_reg(I2CInstance inst, uint8_t DevAddr, uint8_t RegAddr, uint8_t *data, uint32_t size);
extern void drv_i2c_read_reg(I2CInstance inst, uint8_t DevAddr, uint8_t RegAddr, uint8_t *data, uint32_t size);


#endif
