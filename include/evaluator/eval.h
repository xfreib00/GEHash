/**
 * @file eval.h
 * @author Adam Freiberg
 * @brief Header file for Eval class
 */

#pragma once

#include <stack>
#include "auxiliary.h"

template<typename T>
class Eval
{

public:
    /**
     * @brief Construct a new Eval object
     */
    Eval() = default;

    /**
     * @brief Default class constructor.
     */
    Eval(std::queue<Token<T>> t_queue, const T& m);

    /**
     * @brief Evaluate expresion and return result.
     * @return Return calculated result.
     */

    auto eval(const T& hash, const T& key);

    /**
     * @brief Default class destructor.
     */
    ~Eval() = default;

private:
    std::queue<Token<T>> q;
    std::stack<Token<T>> st;
    T magic;
};