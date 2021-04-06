/**
 * @file math_func.cpp
 * @author Adam Freiberg
 * @brief Source file of math functions used by Operators
 */

#include "math_func.h"

template<typename T, typename U>
auto add(const T& a, const U& b)
{
    return a + b;
}

template<typename T, typename U>
auto sub(const T& a, const U& b)
{
    return a - b;
}

template<typename T, typename U>
auto mul(const T& a, const U& b)
{
    return a * b;
}

template<typename T, typename U>
auto div(const T& a, const U& b)
{
    if(b == 0){
        throw std::runtime_error("Error: division by zero");
    }
    return a / b;
}

template<typename T, typename U>
auto mod(const T& a, const U& b)
{
    if(b == 0){
        throw std::runtime_error("Error: division by zero");
    }
    return a % b;
}

template<typename T, typename U>
auto xorf(const T& a, const U& b)
{
    return a ^ b;
}

template<typename T, typename U>
auto shr(const T& a, const U& b)
{
    return a >> b;
}

template<typename T, typename U>
auto shl(const T& a, const U& b)
{
    return a << b;
}

template<typename T>
T neg(const T& a)
{
    return ~a;
}

template<typename T, typename U>
auto andf(const T& a, const U& b)
{
    return a & b;
}

template<typename T, typename U>
auto orf(const T& a, const U& b)
{
    return a | b;
}