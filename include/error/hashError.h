/**
 * @file hashError.h
 * @author Adam Freiberg
 * @brief Header file for hash table exceptions
 */

#pragma once

#include <stdexcept>

/**
 * @brief Standard exception for HTable.
 */
class hashTableError : public std::exception{
    public:
        const char *what() const throw()
        {
            return "Error occured while using HTable class.";
        }
};

/**
 * @brief Exception for HTable::Insert operation.
 */
class hashInsertError : public hashTableError{
    public:
        const char *what() const throw()
        {
            return "Given index already used.";
        }
};

/**
 * @brief Exception for HTable::Remove operation.
 */
class hashRemoveError : public hashTableError{
    public:
        const char *what() const throw()
        {
            return "No such key is stored in given table";
        }

};

/**
 * @brief Exception for HTable::Search operation.
 */
class hashSearchError : public hashTableError {
    public:
        const char *what() const throw()
        {
            return "No such key is stored in given table";
        }

};

/**
 * @brief Exception for Lua evaluation errors..
 */
class hashLuaError : public hashTableError {
    public:
        const char *what() const throw()
        {
            return "Could not execute given string";
        }
};

/**
 * @brief Exception for HTable.func member.
 */
class hashFuncError : public hashTableError {
    public:
        const char *what() const throw()
        {
            return "Function for Lua not specified";
        }
};