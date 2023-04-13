/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: app_foc.c
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: FOC 实现
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

#include "app_foc.h"
#include "drv_atim.h"

#define _PI 3.14159265359
#define _PI_2 1.57079632679
#define _PI_3 1.0471975512
#define _2PI 6.28318530718
#define _3PI_2 4.71238898038
#define _PI_6 0.52359877559
#define _SQRT3 1.73205080757

// PWM 计数周期
#define PWM_Period 1000

// 电源电压
float voltage_power_supply = 12.0f;

float _normalizeAngle(float angle)
{
    float a = fmod(angle, _2PI);
    return a >= 0 ? a : (a + _2PI);
}

extern void app_foc_init()
{
    drv_atim_init();
}

/// @brief FOC 计算执行函数
/// @param Uq 期望 Uq
/// @param Ud 期望 Ud
/// @param angle_el 当前电角度
extern void app_foc_handle(float Uq, float Ud, float angle_el)
{
    float Uref;
    float U_alpha, U_beta;
    float T0, T1, T2;
    float Ta, Tb, Tc;
    int sector;
    float angle;

    U_alpha = Ud * cos(angle_el) - Uq * sin(angle_el); // 反park变换
    U_beta = Ud * sin(angle_el) + Uq * cos(angle_el);

    Uref = sqrt(U_alpha * U_alpha + U_beta * U_beta) / voltage_power_supply;

    if (Uref > 0.577)
        Uref = 0.577; // 六边形的内切圆(SVPWM最大不失真旋转电压矢量赋值)根号3/3
    if (Uref < -0.577)
        Uref = -0.577;
    // 判断参考电压矢量所在扇区：
    if (Uq > 0)
        angle_el = _normalizeAngle(angle_el + _PI_2); // 标准化电角度值【0,2pi】，加90度后是参考电压矢量的位置
    else
        angle_el = _normalizeAngle(angle_el - _PI_2);
    // if (Uq > 0)
    //     angle = angle_el + _PI_2; // 标准化电角度值【0,2pi】，加90度后是参考电压矢量的位置
    // else
    //     angle = angle_el - _PI_2;

    sector = (angle / _PI_3) + 1;

    T1 = _SQRT3 * sin(sector * _PI_3 - angle_el) * Uref; // 计算两个相邻电压矢量作用时间
    T2 = _SQRT3 * sin(angle_el - (sector - 1.0) * _PI_3) * Uref;
    T0 = 1 - T1 - T2; // 零矢量作用时间

    switch (sector)
    {
    case 1:
        Ta = T1 + T2 + T0 / 2;
        Tb = T2 + T0 / 2;
        Tc = T0 / 2;
        break;
    case 2:
        Ta = T1 + T0 / 2;
        Tb = T1 + T2 + T0 / 2;
        Tc = T0 / 2;
        break;
    case 3:
        Ta = T0 / 2;
        Tb = T1 + T2 + T0 / 2;
        Tc = T2 + T0 / 2;
        break;
    case 4:
        Ta = T0 / 2;
        Tb = T1 + T0 / 2;
        Tc = T1 + T2 + T0 / 2;
        break;
    case 5:
        Ta = T2 + T0 / 2;
        Tb = T0 / 2;
        Tc = T1 + T2 + T0 / 2;
        break;
    case 6:
        Ta = T1 + T2 + T0 / 2;
        Tb = T0 / 2;
        Tc = T1 + T0 / 2;
        break;
    default:
        Ta = 0;
        Tb = 0;
        Tc = 0;
    }
    drv_atim_set_ccr_a(Ta * PWM_Period);
    drv_atim_set_ccr_b(Tb * PWM_Period);
    drv_atim_set_ccr_c(Tc * PWM_Period);
}