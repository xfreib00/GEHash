/**
 * @file hashTable.h
 * @author Adam Freiberg
 * @brief Header file for HTable class
 */

#ifndef GEHASH_HTABLE
#define GEHASH_HTABLE

#include <string>
#include "error/hashError.h"
#include <limits>
#include <array>
#include "lua.hpp"

using namespace std;

/**
 * @brief Class implementing basic hash table.
 * @tparam T Data type specifying range of hash table indexes.
 */
template <typename T>
class HTable {

public:

    /**
     * @brief HTable constructor.
     */
    HTable() : L(luaL_newstate()){};

    /**
     * @brief Insert element to table.
     * @param [in] key Key to be inserted to table. 
     * @exception If key is already in table hashInsertError exception is thrown.
     */
    void Insert(string key)
    {
        T hash = get_hash(key);
        if (!table[hash].empty()){
            throw hashInsertError();
        } 
        
        table[hash] = key;
    };

    /**
     * @brief Remove element from table.
     * @param [in] key Key to be removed from table.
     * @exception If key is not in table hashRemoveError exception is thrown.
     */
    void Remove(string key)
    {
        T hash = get_hash(key);
        if (table[hash].empty()){
            throw hashRemoveError();
        }
        table[hash].clear();
    };

    /**
     * @brief Find key in table 
     * @param [in] key Key to be found in table.
     * @return Return index if search was successful. Throw exception otherwise.
     * @exception If key is not in table hashSearchError exception is thrown.
     */
    T Search(string key)
    {
        T hash = get_hash(key);
        if (table[hash].empty()){
            throw hashSearchError();
        }
        return hash;
    };

    /**
     * @brief Set function to be evaluated and used in calculating hash value.
     * @param [in] f String representation of generated function.
     */
    void setFunc(string f)
    {
        func = f;
    };

    /**
     * @brief Set magic number used in calculating hash value.
     * @param [in] m Value to be assigned to magic number.
     */
    void setMagic(unsigned long m)
    {
        magic_num = m;
    };

    /**
     * @brief HTable destructor.
     */
    ~HTable()
    {
        lua_close(L);
    };

private:

    /**
     * @brief HTable's function for calculating hash value. 
     * @param [in] key Key to be hashed.
     * @return Calculated hash value.
     * @exception If no function was not set by HTable::setFunc
     * or given string was empty, throw hashFuncError exception.
     * If Lua evaluation fails, throw hashLuaError exception.
     */
    T get_hash(string key)
    {
        if (func.empty()){
            throw hashFuncError();
        }

        unsigned long hash = 0;

        for(size_t i = 0; i < key.length(); i++)
        {
            /* Push current hash function */
            lua_pushinteger(L,hash);
            lua_setglobal(L,"hash");

            /* If magic_number is used, push current value */
            if (magic_num > 0){
                lua_pushinteger(L,magic_num);
                lua_setglobal(L,"magic_num");
            }

            /* Use function from string to compute new hash value */
            int r = luaL_dostring(L,func.c_str());

            /* If expression evaluation was not succesful throw error */
            if (r != LUA_OK){
		        throw hashLuaError();
            }
            
            /* Assign computed value to hash variable */
		    lua_getglobal(L,"hash");
		    hash = static_cast<unsigned long>(lua_tonumber(L,-1));

        }
        /* use xor-folding to return hash value in specified range */
        return (hash>>(sizeof(T)*8)) ^ (hash & ((((T)1<<(sizeof(T)*8))-1)));
    };

    /**
     * @brief HTable index range. 
     */
    T table_size;

    /**
     * @brief Table alocated using std::array
     */
    array<T,numeric_limits<T>::max()> table;

    /**
     * @brief Pointer to lua_State instance.
     */
    lua_State *L;

    /**
     * @brief Magic number used in calculating hash value.
     */
    unsigned long magic_num = 0;

    /**
     * @brief String containing generated hash function.
     */
    string func;
};

#endif