/**
 * @file parser.h
 * @author Adam Freiberg
 * @brief Header file for Parser class
 */

#pragma once

#include <string>
#include "auxiliary.h"

template<typename T>
class Parser
{

public:

    /**
     * @brief Default Parser class constructor.
     */
    Parser() = default;

    /**
     * @brief Parameterized constructor of Parser class object.
     * @param [in out] input String to be parsed.
     * @exception If input string is empty throw.
     */
    Parser(std::string& input);

    /**
     * @brief Parse input string from constructor.
     *
     * @return std::queue<Token<T>> Parsed output queue.
     */
    std::queue<Token<T>> parse();

    /**
     * @brief Default Parser class destructor.
     */
    ~Parser() = default;

private:

    /**
     * @brief Complete input string
     */
    std::string input_str;

    /**
     * @brief Offset in string
     */
    std::size_t offset;

};