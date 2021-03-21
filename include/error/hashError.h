/**
 * @file hashError.h
 * @author Adam Freiberg
 * @brief Header file for hash table exceptions
 */

#include <stdexcept>

class hashInsertError : public std::exception {
    public:
        const char *what() const throw()
        {
            return "Given index already used.";
        }
};

class hashRemoveError : public std::exception {
    public:
        const char *what() const throw()
        {
            return "No such key is stored in given table";
        }

};

class hashSearchError : public std::exception {
    public:
        const char *what() const throw()
        {
            return "No such key is stored in given table";
        }

};

class hashLuaError : public std::exception {
    public:
        const char *what() const throw()
        {
            return "Could not execute given string";
        }
};