/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_as5600.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: AS5600 驱动
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

#include "drv_as5600.h"
#include "drv_i2c.h"
#include "api_logs.h"
#include "sys_lib_inc.h"

#define AS5600_I2C_ADDR (0X36 << 1)
#define AS5600_REG_ZMCO (0X00)
#define AS5600_REG_ZPOS (0X01)
#define AS5600_REG_MPOS (0X03)
#define AS5600_REG_MANG (0X05)
#define AS5600_REG_CONF (0X07)
#define AS5600_REG_ANGLE (0X0E)
#define AS5600_REG_STATUS (0X0B)
#define AS5600_REG_AGC (0X1A)
#define AS5600_REG_MAGNITUDE (0X1B)
#define AS5600_REG_BURN (0XFF)
#define AS5600_RESOLUTION (4096)

#define abs(x) ((x) > 0 ? (x) : -(x))
#define _2PI 6.28318530718

static float angle_data_prev;      // 上次位置
static float full_rotation_offset; // 转过的整圈数

const char tag[] = "AS5600";

extern void drv_as5600_init(void)
{
    uint8_t data[2] = {0x20, 0xC0};
    drv_i2c_init();
    FirmwareDelay(100000);
    drv_i2c_write_reg(I2C_Instance1, AS5600_I2C_ADDR, AS5600_REG_CONF, data, 2);
}

extern uint16_t drv_as5600_read_raw_angle(void)
{
    uint16_t angle = 0;
    uint8_t data[2] = {0};
    // bool stat = true;
    drv_i2c_read_reg(I2C_Instance1, AS5600_I2C_ADDR, AS5600_REG_ANGLE, data, 2);
    // if (false == stat)
    // {
    //     API_LOGE(tag, "Read Error!");
    // }

    angle = (data[0] << 8) + data[1];

    // API_LOGI(tag, "angle = %d", angle);

    return angle;
}

extern float drv_as5600_read_angle(void)
{
    float angle_data = drv_as5600_read_raw_angle();

    float d_angle = angle_data - angle_data_prev;
    if (abs(d_angle) > (0.8 * AS5600_RESOLUTION))
    {
        full_rotation_offset += (d_angle > 0 ? -_2PI : _2PI);
    }
    angle_data_prev = angle_data;

    return (full_rotation_offset + (angle_data / (float)AS5600_RESOLUTION) * _2PI);
}
