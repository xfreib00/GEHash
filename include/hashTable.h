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

    void Set_func(string f)
    {
        func = f;
    };

    /**
     * @brief Default HTable destructor. 
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
     */
    T get_hash(string key)
    {

        unsigned long hash = 0;
        unsigned long magic_num = 0xDEADBEEF;

        for(size_t i = 0; i < key.length(); i++)
        {
            lua_pushinteger(L,hash);
            lua_setglobal(L,"hash");

            lua_pushinteger(L,magic_num);
            lua_setglobal(L,"magic_num");

            /* use function from string to compute new hash value*/
            int r = luaL_dostring(L,func.c_str());

            if (r != LUA_OK){
		        throw hashLuaError();
            }
            
		    lua_getglobal(L,"hash");
		    hash = static_cast<unsigned long>(lua_tonumber(L,-1));

        }

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

    lua_State *L;

    string func;
};

#endif
