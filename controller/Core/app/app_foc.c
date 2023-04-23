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
#include "utl_ffpm.h"

// PWM 计数周期
#define PWM_Period 1000

// 电源电压
static const fq12_t voltage_power_supply = TO_FQ12(12);

inline fq12_t _normalizeAngle(fq12_t angle)
{
    fmold(angle, FQ12_2PI);
    return angle;
}

extern void app_foc_init()
{
    drv_atim_init();
}

/// @brief FOC 计算执行函数
/// @param Uq 期望 Uq
/// @param Ud 期望 Ud
/// @param angle_el 当前电角度
extern void app_foc_handle(fq12_t Uq, fq12_t Ud, fq12_t angle_el)
{
    fq12_t Uref;
    fq12_t U_alpha, U_beta;
    fq12_t T0, T1, T2;
    fq12_t Ta, Tb, Tc;
    uint16_t a, b, c;
    int sector;

    U_alpha = fsub(fmul(Ud, fcos(angle_el)), fmul(Uq, fsin(angle_el))); // 反park变换
    U_beta = fadd(fmul(Ud, fsin(angle_el)), fmul(Uq, fcos(angle_el)));

    Uref = fdiv(fsqrt(fadd(fmul(U_alpha, U_alpha), fmul(U_beta, U_beta))), voltage_power_supply);

    if (Uref > FQ12_SQRT3_DIV3)
        Uref = FQ12_SQRT3_DIV3; // 六边形的内切圆(SVPWM最大不失真旋转电压矢量赋值)根号3/3
    if (Uref < -FQ12_SQRT3_DIV3)
        Uref = -FQ12_SQRT3_DIV3;
    // 判断参考电压矢量所在扇区：
    if (Uq > TO_FQ12(0))
        angle_el = _normalizeAngle(angle_el + FQ12_PI_DIV2); // 标准化电角度值【0,2pi】，加90度后是参考电压矢量的位置
    else
        angle_el = _normalizeAngle(angle_el - FQ12_PI_DIV2);
    // if (Uq > TO_FQ12(0))
    //     angle = angle_el + FQ12_PI_DIV2; // 标准化电角度值【0,2pi】，加90度后是参考电压矢量的位置
    // else
    //     angle = angle_el - FQ12_PI_DIV2;

    sector = FQ12_TO_INT32(fdiv(angle_el, FQ12_PI_DIV3)) + 1;

    T1 = fmul(FQ12_SQRT3, fmul(fsin(fsub(fmul(TO_FQ12(sector), FQ12_PI_DIV3), angle_el)), Uref)); // 计算两个相邻电压矢量作用时间
    T2 = fmul(FQ12_SQRT3, fmul(fsin(fsub(angle_el, fmul(TO_FQ12(sector - 1), FQ12_PI_DIV3))), Uref));
    T0 = TO_FQ12(1) - T1 - T2; // 零矢量作用时间

    switch (sector)
    {
    case 1:
        Ta = fadd(T1, fadd(T2, T0)) >> 1;
        Tb = fadd(T2, T0) >> 1;
        Tc = T0 >> 1;
        break;
    case 2:
        Ta = fadd(T1, T0) >> 1;
        Tb = fadd(T1, fadd(T2, T0)) >> 1;
        Tc = T0 >> 1;
        break;
    case 3:
        Ta = T0 >> 1;
        Tb = fadd(T1, fadd(T2, T0)) >> 1;
        Tc = fadd(T2, T0) >> 1;
        break;
    case 4:
        Ta = T0 >> 1;
        Tb = fadd(T1, T0) >> 1;
        Tc = fadd(T1, fadd(T2, T0)) >> 1;
        break;
    case 5:
        Ta = fadd(T2, T0) >> 1;
        Tb = T0 >> 1;
        Tc = fadd(T1, fadd(T2, T0)) >> 1;
        break;
    case 6:
        Ta = fadd(T1, fadd(T2, T0)) >> 1;
        Tb = T0 >> 1;
        Tc = fadd(T1, T0) >> 1;
        break;
    default:
        Ta = TO_FQ12(0);
        Tb = TO_FQ12(0);
        Tc = TO_FQ12(0);
    }

    // note: 注意是否范围？
    a = FQ12_TO_INT32(fmul(Ta, TO_FQ12(PWM_Period)));
    b = FQ12_TO_INT32(fmul(Tb, TO_FQ12(PWM_Period)));
    c = FQ12_TO_INT32(fmul(Tc, TO_FQ12(PWM_Period)));

    drv_atim_set_ccr_a(a);
    drv_atim_set_ccr_b(b);
    drv_atim_set_ccr_c(c);
}