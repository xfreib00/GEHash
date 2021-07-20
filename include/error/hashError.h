/**
 * @file hashError.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for hash table exceptions
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "GEHashError.h"

/**
 * @brief Standard exception for HTable.
 */
class hashTableError : public GEHashError {
  public:
    const char *what() const throw() {
        return "Error occured while using HTable class.";
    }
};

/**
 * @brief Exception for HTable::Insert operation.
 */
class hashInsertError : public hashTableError {
  public:
    const char *what() const throw() { return "Given index already used."; }
};

/**
 * @brief Exception for HTable::Remove operation.
 */
class hashRemoveError : public hashTableError {
  public:
    const char *what() const throw() {
        return "No such key is stored in given table";
    }
};

/**
 * @brief Exception for HTable::Search operation.
 */
class hashSearchError : public hashTableError {
  public:
    const char *what() const throw() {
        return "No such key is stored in given table";
    }
};

/**
 * @brief Exception for HTable.func member.
 */
class hashFuncError : public hashTableError {
  public:
    const char *what() const throw() { return "Hash function not specified"; }
};