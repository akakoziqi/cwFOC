/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_i2c.h
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: I2C 驱动
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Email: akako.ziqi@outlook.com
 *
 * Copyright (C) 2023 akako
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
