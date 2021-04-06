/**
 * @file eval.cpp
 * @author Adam Freiberg
 * @brief Source file for Eval class methods
 */

#pragma once

#include "evaluator/eval.h"

template<typename T>
Eval<T>::Eval(std::queue<Token<T>> t_queue, const T& m)
{
    q = t_queue;
    magic = m;
};

template<typename T>
auto Eval<T>::eval(const T& hash, const T& key)
{
    var v = {"hash", hash};
    var u = {"key", key};
    while (!q.empty())
    {
        if(isOperator<T>(q.front())){

        }
    }

};

template<typename T>
static bool isOperator(Token<T> t)
{
    return std::holds_alternative<Operator<T>>(t);
};