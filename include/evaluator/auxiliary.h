/**
 * @file auxiliary.h
 * @author Adam Freiberg
 * @brief Header file for paser and eval support classes and typedefs
 */

#ifndef AUX_H
#define AUX_H

#include <functional>
#include <queue>
#include <variant>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include "math_func.h"

template<typename T>
class Operator
{
private:
    /* data */
public:

    /**
     * @brief Default class constructor.
     */
    Operator() = default;

    /**
     * @brief Parameterized constructor of Operator class.
     * @param [in] prec Precedence level of Operator
     * @param [in] asoc Asociativity of Operator
     * @param [in] symb Symbol used as Operator
     * @param [in] bin Flag is Operator is binary
     * @param [in] fn Function pointer to operation implementation
     */
    Operator(uint8_t prec, Asociativity asoc, char symb, bool bin, Function<T> fn)
    {
        precedence = prec;
        a = asoc;
        symbol = symb;
        binary = bin;
        func = fn;
    };

    /**
     * @brief Default class destructor.
     */
    ~Operator() = default;

    /**
     * @brief Precedence level.
     * @details Lowest correct value is 1. If value is 0, then operator is invalid.
     */
    uint8_t precedence = 0;

    /**
     * @brief Asociativity of operator
     * @details Direction of opearator's asociativity. If not defined, value is NDEF.
     */
    Asociativity a = NDEF;

    /**
     * @brief Symbol representing operator.
     * @details Symbol used to represent given operator. If not defined, value is nullptr.
     */
    char symbol = nullptr;

    /**
     * @brief Is operator binary?
     * @details Defines is operator is unary or binary. Defaults to false.
     */
    bool binary = false;

    /**
     * @brief Pointer to function used by operator.
     * @details Pointer to function used when calling operator. If not defined, value is nullptr.
     */
    Function<T> func = nullptr;

};

/**
 * @brief Alias for std::variant with Operator.
 *
 * @tparam T Type of std::variant first parameter.
 */
template<typename T>
using Token = std::variant<T, Operator>;

/**
 * @brief Alias for std::function.
 *
 * @tparam T Type of std::function args.
 */
template<typename T>
using Function = std::function<auto(T,T)>;

/**
 * @enum Asociativity
 * @brief Asociativity of operator.
 */
enum Asociativity
{
    LEFT,   /**< Operator with left asociativity */
    RIGHT,  /**< Operator with right asociativity */
    NDEF    /**< Not defined asociativity */
};

/**
 * @brief Unordered map of operators.
 *
 * @tparam T Type used for Operator function.
 */
template<typename T>
const std::unordered_map<char, Operator<T>> operator_map
{
    {'+', Operator(5, LEFT, '+', true, add)},
    {'-', Operator(5, LEFT, '-', true, sub)},
    {'*', Operator(6, LEFT, '*', true, mul)},
    {'/', Operator(6, LEFT, '/', true, div)},
    {'^', Operator(2, LEFT, '^', true, xorf)},
    {'~', Operator(7, RIGHT, '~', false, neg)},
    {'%', Operator(6, LEFT, '%', true, mod)},
    {'|', Operator(1, RIGHT, '|', true, orf)},
    {'&', Operator(3, RIGHT, '&', true, andf)}
};

/**
 * @brief Unordered map of shift operators.
 *
 * @tparam T Type of Operator function.
 */
template<typename T>
const std::unordered_map<std::string, Operator<T>> shift_op_map
{
    {"<<", Operator(4, RIGHT, 'l', true, shl)},
    {">>", Operator(4, RIGHT, 'r', true, shr)}
};

/**
 * @brief Unordered map of parantheses.
 *
 * @tparam T Type of Operator function.
 */
template<typename T>
const std::unordered_map<char, Operator<T>> par_map
{
    {'(', Operator(0, LEFT, '(', true, nullptr)},
    {')', Operator(0, LEFT, ')', true, nullptr)}
};

/**
 * @brief
 *
 * @tparam T
 */
template <typename T>
using var = std::pair<std::string, T>;

#endif