#ifndef __DRV_AS5600_H__
#define __DRV_AS5600_H__

#include "sys_inc.h"

extern void drv_as5600_init(void);
extern uint16_t drv_as5600_read_raw_angle(void);
extern float drv_as5600_read_angle(void);

#endif