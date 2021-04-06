/**
 * @file math_func.h
 * @author Adam Freiberg
 * @brief Header file containing function used in Operator class
 */

#pragma once

#include <stdexcept>

/**
 * @brief Function for adding two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Second value
 * @return auto Addition result.
 */
template <typename T, typename U>
auto add(const T &a, const U &b);

/**
 * @brief Function for substracting two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Second value
 * @return auto Substraction result.
 */
template <typename T, typename U>
auto sub(const T &a, const U &b);

/**
 * @brief Function for multiplying two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a Multiplier value
 * @param b Multiplicand value
 * @return auto Multiplication result.
 */
template <typename T, typename U>
auto mul(const T &a, const U &b);

/**
 * @brief Function for dividing two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a Numerator value
 * @param b Denominator value
 * @return auto Division result.
 * @exception If b is zero throw std::runtime_error.
 */
template <typename T, typename U>
auto div(const T &a, const U &b);

/**
 * @brief Function for modulo of two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Denominator value
 * @return auto Modulo result.
 * @exception If b is zero throw std::runtime_error.
 */
template <typename T, typename U>
auto mod(const T &a, const U &b);

/**
 * @brief Function for xor of two values.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Second value
 * @return auto Xored result.
 */
template <typename T, typename U>
auto xorf(const T &a, const U &b);

/**
 * @brief Function for right bitwise shift.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a Value to be shifted
 * @param b Offset
 * @return auto Shifted value.
 */
template<typename T, typename U>
auto shr(const T& a, const U& b);

/**
 * @brief Function for left bitwise shift.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a Value to be shifted
 * @param b Offset
 * @return auto Shifted value.
 */
template<typename T, typename U>
auto shl(const T& a, const U& b);

/**
 * @brief Function for bitwise negation of value.
 *
 * @tparam T Type of argument
 * @param a Value to be negated
 * @return T Negated value
 */
template<typename T>
T neg(const T& a);

/**
 * @brief Function for bitwise AND operation.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Second value
 * @return auto Result of bitwise AND.
 */
template<typename T, typename U>
auto andf(const T& a, const U& b);

/**
 * @brief Function for bitwise OR operation.
 *
 * @tparam T Type of first argument
 * @tparam U Type of second argument
 * @param a First value
 * @param b Second value
 * @return auto Result of bitwise OR.
 */
template<typename T, typename U>
auto orf(const T& a, const U& b);