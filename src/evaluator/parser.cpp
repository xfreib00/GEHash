/**
 * @file parser.cpp
 * @author Adam Freiberg
 * @brief Source file for Parser class methods
 */

#include "evaluator/parser.h"

template<typename T>
Parser<T>::Parser(std::string& input)
{
    input_str.assign(input);
    offset = 0;
}

template<typename T>
std::queue<Token<T>> Parser<T>::parse()
{

}
