/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 文件名: utl_ffpm.h
 * 作者: akako
 * 修订版本: 1.0
 * 最后编辑: akako
 * 内容摘要: Fxcking Fixed-point Mathematics !
 * 参考：https://github.com/XiangYyang/G8Driver/blob/main/mcu/src/utils/mu_fixed.c
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

#ifndef __UTL_FFPM_H__
#define __UTL_FFPM_H__

#include <stdint.h>

typedef int32_t fq12_t;

// 将一个值转为 Q12 定点数
#define TO_FQ12(x) (fq12_t)((x) * (1 << 12))

// 将一个 Q12 定点数转为 float64
#define FQ12_TO_FP64(x) ((x) / (double)(1 << 12))

// 将一个 Q12 定点数抛弃小数位转为 int32
#define FQ12_TO_INT32(x) ((int32_t)(x >> 12))

// 常用数值
#define FP64_PI (3.14159265359)
#define FP64_SQRT3 (1.732050808)
#define FP64_SQRT2 (1.414213562)

#define FQ12_PI (TO_FQ12(FP64_PI))
#define FQ12_PI_DIV2 (TO_FQ12(FP64_PI / 2))
#define FQ12_PI_DIV3 (TO_FQ12(FP64_PI / 3))
#define FQ12_2PI (TO_FQ12(FP64_PI * 2))

#define FQ12_SQRT3 (TO_FQ12(FP64_SQRT3))
#define FQ12_SQRT3_DIV3 (TO_FQ12(FP64_SQRT3 / 3))
#define FQ12_SQRT2 (TO_FQ12(FP64_SQRT2)) 

// 加法
#define fadd(a, b) ((a) + (b))
// 减法
#define fsub(a, b) ((a) - (b))
// 乘法，注意溢出
#define fmul(a, b) (((a) * (b)) >> 12)
// 除法，注意溢出
#define fdiv(a, b) (((a) << 12) / (b))
// 除法，低精度，注意精度
#define fdiv2(a, b) ((((a) << 6) / (b)) << 5)
// 取余，注意时间不固定
#define fmold(a, b)       \
    {                     \
        while ((a) > (b)) \
            (a) -= (b);   \
    }


extern fq12_t flog2(fq12_t x);
extern fq12_t fsqrt(fq12_t x);
extern fq12_t fsin(fq12_t x);
extern fq12_t fcos(fq12_t x);

#endif
