/**
 * @file geError.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Exception classes for GEHash class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "GEHashError.h"

/**
 * @brief Standard exception for GEHash.
 */
class geError : public GEHashError {
  public:
    const char *what() const throw() {
        return "Error occured while using GEHash class.";
    }
};

/**
 * @brief Tournament size exception.
 */
class geTournamentError : public geError {
  public:
    const char *what() const throw() {
        return "Tournament size out of range. Must be more than 1.";
    }
};

/**
 * @brief Mutation probability exception.
 */
class geMutationError : public geError {
  public:
    const char *what() const throw() {
        return "Mutation probability is out of range. Must be between 0 and 1.";
    }
};

/**
 * @brief Population size exception.
 */
class gePopulationError : public geError {
  public:
    const char *what() const throw() {
        return "Population is out of range. Must be more than 10.";
    }
};

/**
 * @brief Generaion number exception.
 */
class geGenerationError : public geError {
  public:
    const char *what() const throw() {
        return "Number of generations is out of range. Must be more than 2.";
    }
};

/**
 * @brief Grammar string exception.
 */
class geGrammarError : public geError {
  public:
    const char *what() const throw() { return "Gramar string is empty."; }
};