/**
 * @file loggerError.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for GELogger exceptions
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "GEHashError.h"

/**
 * @brief Standard exception for GELogger.
 */
class loggerError : public GEHashError {
  public:
    const char *what() const throw() {
        return "GELogger: Error occurred while using GELogger class.";
    }
};

/**
 * @brief GELogger input file exception.
 */
class loggerInputError : public loggerError {
  public:
    const char *what() const throw() {
        return "GELogger: given file is empty.";
    }
};

/**
 * @brief GELogger open file exception.
 */
class loggerOpenError : public loggerError {
  public:
    const char *what() const throw() {
        return "GELogger: Could not open/create given file.";
    }
};