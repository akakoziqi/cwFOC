/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: drv_i2c.c
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

#include "drv_i2c.h"
#include "sys_lib_inc.h"

#define DEVICE_INST(d) ((I2C_TypeDef *)(d))
#define I2C_READ (0x01)
#define I2C_WRITE (0x00)

const I2CInstance I2C_Instance1 = (I2CInstance)(CW_I2C1);
const I2CInstance I2C_Instance2 = (I2CInstance)(CW_I2C2);

static inline void drv_i2c_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOF, ENABLE);

    PF00_AFx_I2C1SDA();
    PF01_AFx_I2C1SCL();

    GPIO_InitStructure.Pins = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOF, &GPIO_InitStructure);

}

extern void drv_i2c_init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    drv_i2c_gpio_init();
    RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_I2C1, ENABLE);

    I2C_InitStruct.I2C_BaudEn = ENABLE;
    I2C_InitStruct.I2C_Baud = 3; // 2M=(64000000/(8*(BRR+1)); BRR = 3
    I2C_InitStruct.I2C_FLT = DISABLE;
    I2C_InitStruct.I2C_AA = DISABLE;
    I2C1_DeInit();
    I2C_Master_Init(CW_I2C1, &I2C_InitStruct); // 初始化模块
    I2C_Cmd(CW_I2C1, ENABLE);                  // 模块使能
}

extern void drv_i2c_write_reg(I2CInstance inst, uint8_t DevAddr, uint8_t RegAddr, uint8_t *data, uint32_t size)
{
    uint32_t cnt = 0;

    I2C_GenerateSTART(DEVICE_INST(inst), ENABLE);
    
    while (1)
    {
        while (0 == I2C_GetIrq(DEVICE_INST(inst)))
        {
            ;
        }
        
        switch (I2C_GetState(DEVICE_INST(inst)))
        {
        case 0x08: // 发送完START信号
            I2C_GenerateSTART(DEVICE_INST(inst), DISABLE);
            I2C_Send7bitAddress(DEVICE_INST(inst), DevAddr, I2C_WRITE); // 从设备地址+W发送
            break;
        case 0x18: // 发送完SLA+W信号
            // 发送片内地址
            I2C_SendData(DEVICE_INST(inst), RegAddr);
            break;
        case 0x28: // 发送完1字节数据：发送EEPROM中memory地址也会产生，发送后面的数据也会产生
            I2C_SendData(DEVICE_INST(inst), data[cnt++]);
            break;
        case 0x20: // 发送完SLA+W后从机返回NACK
        case 0x38: // 主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
            I2C_GenerateSTART(DEVICE_INST(inst), ENABLE);
            break;
        case 0x30: // 发送完一个数据字节后从机返回NACK
            I2C_GenerateSTOP(DEVICE_INST(inst), ENABLE);
            break;
        default:
            break;
        }

        if (cnt > size)
        {
            I2C_GenerateSTOP(DEVICE_INST(inst), ENABLE); // 此顺序不能调换，出停止条件
            I2C_ClearIrq(DEVICE_INST(inst));
            break;
        }
        I2C_ClearIrq(DEVICE_INST(inst));
    }
}

extern void drv_i2c_read_reg(I2CInstance inst, uint8_t DevAddr, uint8_t RegAddr, uint8_t *data, uint32_t size)
{
    uint32_t cnt = 0;

    I2C_GenerateSTART(DEVICE_INST(inst), ENABLE);


    while (1)
    {
        while (0 == I2C_GetIrq(DEVICE_INST(inst)))
        {
            ;
        }

        switch (I2C_GetState(DEVICE_INST(inst)))
        {
        case 0x08: // 发送完START信号
            I2C_GenerateSTART(DEVICE_INST(inst), DISABLE);
            I2C_Send7bitAddress(DEVICE_INST(inst), DevAddr, I2C_WRITE); // 发送从机地址
            break;
        case 0x18: // 发送完SLA+W/R字节
            I2C_SendData(DEVICE_INST(inst), RegAddr);
            break;
        case 0x28:              // 发送完1字节数据：发送EEPROM中memory地址也会产生，发送后面的数据也会产生
            DEVICE_INST(inst)->CR_f.STA = 1; // set start        //发送重复START信号,START生成函数改写后，会导致0X10状态被略过，故此处不调用函数
            break;
        case 0x10: // 发送完重复起始信号
            I2C_GenerateSTART(DEVICE_INST(inst), DISABLE);
            I2C_Send7bitAddress(DEVICE_INST(inst), DevAddr, I2C_READ);
            break;
        case 0x40: // 发送完SLA+R信号，开始接收数据
            if (size > 1)
            {
                I2C_AcknowledgeConfig(DEVICE_INST(inst), ENABLE);
            }
            break;
        case 0x50: // 接收完一字节数据，在接收最后1字节数据之前设置AA=0;
            data[cnt++] = I2C_ReceiveData(DEVICE_INST(inst));
            if (cnt == size - 1)
            {
                I2C_AcknowledgeConfig(DEVICE_INST(inst), DISABLE);
            }
            break;
        case 0x58: // 接收到一个数据字节，且NACK已回复
            data[cnt++] = I2C_ReceiveData(DEVICE_INST(inst));
            I2C_GenerateSTOP(DEVICE_INST(inst), ENABLE);
            break;
        case 0x38: // 主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
            I2C_GenerateSTART(DEVICE_INST(inst), ENABLE);
            break;
        case 0x48: // 发送完SLA+R后从机返回NACK
            I2C_GenerateSTOP(DEVICE_INST(inst), ENABLE);
            I2C_GenerateSTART(DEVICE_INST(inst), ENABLE);
            break;
        default:
            I2C_GenerateSTART(DEVICE_INST(inst), ENABLE); // 其他错误状态，重新发送起始条件
            break;
        }
        I2C_ClearIrq(DEVICE_INST(inst));

        if (cnt == size)
        {
            break;
        }
    }
}
