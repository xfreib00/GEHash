/**
 * @file GEHashError.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Base class for GEHash exceptions
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <stdexcept>

namespace GEHash {

/**
 * @brief Namespace for all custom GEHash project exceptions
 */
namespace GEHashError {

/**
 * @brief Base class for GEHash exception.
 */
class GEHashError : public std::exception {
  public:
    const char *what() const throw() { return "GEHash error."; }
};

} // namespace GEHashError
} // namespace GEHash