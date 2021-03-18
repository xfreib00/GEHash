/**
 * @file hashError.h
 * @author Adam Freiberg
 * @brief Header file for hash table exceptions
 */

#include <stdexcept>

class hashInitError : public std::exception{
    public:
        const char *what() const throw()
        {
            return "Given size must be in int range.";
        }
};

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