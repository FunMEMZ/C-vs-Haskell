/*
 * 任务：数学计算 —— 加减乘除；幂指对；三角函数；反三角函数；双曲函数；gcd。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 01_01_math_basic_calculations.c -lm
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
#define E  2.71828182845904523536


/* ---------- 加减乘除 ---------- */

static void arithmetic_demo(void) {
    int a = 17, b = 5;
    printf("int:  a+b=%d, a-b=%d, a*b=%d, a/b=%d, a%%b=%d\n",
           a + b, a - b, a * b, a / b, a % b);

    double x = 17.0, y = 5.0;
    printf("real: x+y=%.3f, x-y=%.3f, x*y=%.3f, x/y=%.3f\n",
           x + y, x - y, x * y, x / y);
}


/* ---------- 幂、指数、对数 ---------- */

static void power_exp_log_demo(void) {
    printf("pow(2,10)=%.1f\n", pow(2.0, 10.0));
    printf("exp(1)=%.6f\n", exp(1.0));
    printf("log(e)=%.6f, log10(1000)=%.6f, log2(8)=%.6f\n",
           log(E), log10(1000.0), log(8.0) / log(2.0));
    printf("sqrt(2)=%.6f\n", sqrt(2.0));
}


/* ---------- 三角函数 ---------- */

static void trig_demo(void) {
    double deg_to_rad = PI / 180.0;
    printf("sin30=%.6f, cos60=%.6f, tan45=%.6f\n",
           sin(30.0 * deg_to_rad),
           cos(60.0 * deg_to_rad),
           tan(45.0 * deg_to_rad));
}


/* ---------- 反三角函数 ---------- */

static void inverse_trig_demo(void) {
    printf("asin(0.5)=%.6f rad\n", asin(0.5));
    printf("acos(0.5)=%.6f rad\n", acos(0.5));
    printf("atan(1)=%.6f rad\n", atan(1.0));
    printf("atan2(1,1)=%.6f rad\n", atan2(1.0, 1.0));
}


/* ---------- 双曲函数 ---------- */

static void hyperbolic_demo(void) {
    printf("sinh(1)=%.6f, cosh(1)=%.6f, tanh(1)=%.6f\n",
           sinh(1.0), cosh(1.0), tanh(1.0));
    printf("asinh(1)=%.6f, acosh(2)=%.6f, atanh(0.5)=%.6f\n",
           asinh(1.0), acosh(2.0), atanh(0.5));
}


/* ---------- gcd ---------- */

static long long gcd_ll(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}


int main(void) {
    arithmetic_demo();
    printf("\n");
    power_exp_log_demo();
    printf("\n");
    trig_demo();
    printf("\n");
    inverse_trig_demo();
    printf("\n");
    hyperbolic_demo();
    printf("\n");
    printf("gcd(48, 18) = %lld\n", gcd_ll(48, 18));
    printf("gcd(-48, 18) = %lld\n", gcd_ll(-48, 18));
    return 0;
}