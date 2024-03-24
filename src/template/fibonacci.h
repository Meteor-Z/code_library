/**
 * @file fibonacci.h
 * @author lzc (liuzechen.coder@qq.com)
 * @brief 网上看的，使用模板在编译期计算斐波那契数列
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CODE_TEMPLATE_FIBONACCI_H
#define CODE_TEMPLATE_FIBONACCI_H

template <int N>
struct Fib {
    inline static constexpr long long value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <>
struct Fib<0> {
    inline static constexpr long long value = 1;
};

template <>
struct Fib<1> {
    inline static constexpr long long value = 1;
};

#endif