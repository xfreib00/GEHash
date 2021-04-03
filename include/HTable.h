/**
 * @file HTable.h
 * @author Adam Freiberg
 * @brief Header only hash table implementation
 */

#ifndef GEHASH_HTABLE
#define GEHASH_HTABLE

#include <string>
#include "error/hashError.h"
#include <limits>
#include <array>
#include <vector>
#include "lua.hpp"

using namespace std;

/**
 * @brief Class implementing basic hash table.
 * @tparam T Data type specifying range of hash table indexes.
 * @tparam V Data type of records.
 */
template <typename T,typename V>
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
    void Insert(V key)
    {
        if (T hash = get_hash(key); table[hash].empty()){
            table[hash].push_back(key);
        }
        else{
             auto it = table[hash].begin();

            for (; it != table[hash].end(); ) {
                if (*it == key){
                    throw hashInsertError();
                }
                else{
                    it++;
                }
            }
        }
    };

    /**
     * @brief Remove element from table.
     * @param [in] key Key to be removed from table.
     * @exception If key is not in table hashRemoveError exception is thrown.
     */
    void Remove(V key)
    {
        T hash = get_hash(key);
        if (table[hash].empty()){
            throw hashRemoveError();
        }

        auto it = table[hash].begin();

        for (; it != table[hash].end(); ) {
            if (*it == key){
                it = table[hash].erase(it);
                break;
            }
            else{
                it++;
            }
        }
        if (it == table[hash].end()){
            throw hashRemoveError();
        }
    };

    /**
     * @brief Find key in table.
     * @param [in] key Key to be found in table.
     * @return Return index if search was successful. Throw exception otherwise.
     * @exception If key is not in table hashSearchError exception is thrown.
     */
    T Search(V key)
    {
        T hash = get_hash(key);
        if (table[hash].empty()){
            throw hashSearchError();
        }

        auto it = table[hash].begin();

        for (; it != table[hash].end(); ) {
            if (*it == key){
                return hash;
            }
            else{
                it++;
            }
        }

        throw hashSearchError();
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
    void setMagic(uint64_t m)
    {
        magic_num = m;
    };

    /**
     * @brief Function returns size of table.
     * @return Size of table.
     */
    T getSize(void)
    {
        return table.size();
    };

    /**
     * @brief Function fills given array with element count.
     * at each index of hash table.
     * @return Array filled with elemenent count for each index of HTable.
     */
    array<T,numeric_limits<T>::max()> getDimensions(void)
    {
        array <T,numeric_limits<T>::max()> arr;
        for (T i = 0; i < table.size(); i++){
            arr[i] = table[i].size();
        }
        return arr;
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
    T get_hash(V key)
    {
        if (func.empty()){
            throw hashFuncError();
        }

        /* initial value of hash */
        uint64_t hash = 0;

        for(auto& k : key)
        {
            /* Push current hash function */
            lua_pushinteger(L,hash);
            lua_setglobal(L,"hash");

            /* Push current index of key */
            lua_pushinteger(L,k);
            lua_setglobal(L,"key");

            /* If magic_number is used, push current value */
            if (magic_num > 0){
                lua_pushinteger(L,magic_num);
                lua_setglobal(L,"magic");
            }

            /* Use function from string to compute new hash value */
            int r = luaL_dostring(L,func.c_str());

            /* If expression evaluation was not succesful throw error */
            if (r != LUA_OK){
		        throw hashLuaError();
            }

            /* Assign computed value to hash variable */
		    lua_getglobal(L,"hash");
		    hash = static_cast<uint64_t>(lua_tonumber(L,-1));

        }
        /* use xor-folding to return hash value in specified range */
        return (hash>>(sizeof(T)*8)) ^ (hash & ((((T)1<<(sizeof(T)*8))-1)));
    };

    /**
     * @brief Table alocated using std::array
     */
    array<vector<V>,numeric_limits<T>::max()> table;

    /**
     * @brief Pointer to lua_State instance.
     */
    lua_State *L;

    /**
     * @brief Magic number used in calculating hash value.
     */
    uint64_t magic_num = 0;

    /**
     * @brief String containing generated hash function.
     */
    string func;
};

#endif