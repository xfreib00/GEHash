/**
 * @file loggerError.h
 * @author Adam Freiberg
 * @brief Header file for GELogger exceptions
 */

#pragma once

#include <stdexcept>

/**
 * @brief Standard exception for GELogger.
 */
class loggerError : public std::exception{
    public:
        const char *what() const throw()
        {
            return "Error occured while using GELogger class.";
        }
};

/**
 * @brief GELogger input file exception.
 */
class loggerInputError : public std::exception{
    public:
        const char *what() const throw()
        {
            return "GELogger: given file is empty.";
        }
};

/**
 * @brief GELogger open file exception.
 */
class loggerOpenError : public std::exception{
    public:
        const char *what() const throw()
        {
            return "GELogger: Could not open/create given file.";
        }
};