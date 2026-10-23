/* Exercise 2-1: Write a program to determine the ranges of char, short,
 * int, and long variables, both signed and unsigned, by printing
 * appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of the various
 * floating-point types.
 */

#include <float.h>
#include <limits.h>
#include <stdio.h>

/* 方法一：直接打印标准头文件 <limits.h> 中定义的宏 */
void via_headers(void)
{
    printf("--- 方法一：来自 <limits.h> ---\n");
    printf("signed char:    %d 到 %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char:  0 到 %u\n", UCHAR_MAX);
    printf("signed short:   %d 到 %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 到 %u\n", USHRT_MAX);
    printf("signed int:     %d 到 %d\n", INT_MIN, INT_MAX);
    printf("unsigned int:   0 到 %u\n", UINT_MAX);
    printf("signed long:    %ld 到 %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long:  0 到 %lu\n", ULONG_MAX);
    printf("\n");
}

/* 方法二：直接计算。
   补码表示下：
     - 无符号最大值 = 所有位全为 1
     - 有符号最大值 = 无符号最大值右移 1 位（去掉符号位）
     - 有符号最小值 = -有符号最大值 - 1                              */
void via_computation(void)
{
    unsigned char uc_max = ~(unsigned char)0; /* 8 位全 1 */
    unsigned short us_max = ~(unsigned short)0;
    unsigned int ui_max = ~(unsigned int)0;
    unsigned long ul_max = ~(unsigned long)0;

    signed char sc_max = (signed char)(uc_max >> 1);
    signed short ss_max = (signed short)(us_max >> 1);
    signed int si_max = (signed int)(ui_max >> 1);
    signed long sl_max = (signed long)(ul_max >> 1);

    signed char sc_min = -sc_max - 1;
    signed short ss_min = -ss_max - 1;
    signed int si_min = -si_max - 1;
    signed long sl_min = -sl_max - 1;

    printf("--- 方法二：直接计算 ---\n");
    printf("signed char:    %d 到 %d\n", sc_min, sc_max);
    printf("unsigned char:  0 到 %u\n", uc_max);
    printf("signed short:   %d 到 %d\n", ss_min, ss_max);
    printf("unsigned short: 0 到 %u\n", us_max);
    printf("signed int:     %d 到 %d\n", si_min, si_max);
    printf("unsigned int:   0 到 %u\n", ui_max);
    printf("signed long:    %ld 到 %ld\n", sl_min, sl_max);
    printf("unsigned long:  0 到 %lu\n", ul_max);
    printf("\n");
}

/* 浮点类型的范围无法直接计算，直接打印 <float.h> 中的宏 */
void floating(void)
{
    printf("--- 浮点类型（来自 <float.h>）---\n");
    printf("float:        %g 到 %g（最小精度 %g）\n", FLT_MIN, FLT_MAX, FLT_EPSILON);
    printf("double:       %g 到 %g（最小精度 %g）\n", DBL_MIN, DBL_MAX, DBL_EPSILON);
}

int main(void)
{
    via_headers();
    via_computation();
    floating();
    return 0;
}
