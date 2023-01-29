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

namespace GEHash {
namespace GEHashError {

/**
 * @brief Standard exception for GEHash.
 */
class geError : public GEHashError {
  public:
    const char *what() const throw() {
        return "GEHash: Error occurred while using GEHash class.";
    }
};

/**
 * @brief Tournament size exception.
 */
class geTournamentError : public geError {
  public:
    const char *what() const throw() {
        return "GEHash: Tournament size out of range. Must be more than 1.";
    }
};

/**
 * @brief Mutation probability exception.
 */
class geMutationError : public geError {
  public:
    const char *what() const throw() {
        return "GEHash: Mutation probability is out of range. Must be between "
               "0 and 1.";
    }
};

/**
 * @brief Population size exception.
 */
class gePopulationError : public geError {
  public:
    const char *what() const throw() {
        return "GEHash: Population is out of range. Must be more than 10.";
    }
};

/**
 * @brief Generation number exception.
 */
class geGenerationError : public geError {
  public:
    const char *what() const throw() {
        return "GEHash: Number of generations is out of range. Must be more "
               "than 2.";
    }
};

/**
 * @brief Grammar string exception.
 */
class geGrammarError : public geError {
  public:
    const char *what() const throw() {
        return "GEHash: Grammar string is empty.";
    }
};

} // namespace GEHashError
} // namespace GEHash