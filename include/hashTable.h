/**
 * @file hashTable.h
 * @author Adam Freiberg
 * @brief Header file for HTable class
 */

#ifndef GEHASH_HTABLE
#define GEHASH_HTABLE

#include <string>
#include <cstdlib>
#include "error/hashError.h"

using namespace std;

class HTable {

public:

    HTable() = delete;

    /**
     * @brief HTable constructor.
     * @param [in] size Size of hash table.
     */
    HTable(uint32_t size)
    {
        if (size <= 0){
            throw hashInitError();
        }

        table_size = size;
        table[table_size];
    };

    /**
     * @brief Insert element to table.
     * @param [in] key Key to be inserted to table. 
     * @exception If key is already in table throw.
     */
    void Insert(string key)
    {
        int hash = get_hash(key);
        if (!table[hash].empty()){
            throw hashInsertError();
        } 
        
        table[hash] = key;
    };

    /**
     * @brief Remove element from table.
     * @param [in] key Key to be removed from table.
     * @exception If key is not in table throw.
     */
    void Remove(string key)
    {
        int hash = get_hash(key);
        if (table[hash].empty()){
            throw hashRemoveError();
        }
        table[hash].clear();
    };

    /**
     * @brief Find key in table 
     * @param [in] key Key to be found in table.
     * @return Return index if search was successful. Throw exception otherwise.
     * @exception If key is not in table throw.
     */
    uint32_t Search(string key)
    {
        int hash = get_hash(key);
        if (table[hash].empty()){
            throw hashSearchError();
        }
        return hash;
    };

    /**
     * @brief Default HTable destructor. 
     */
    ~HTable() = default;

private:

    /**
     * @brief HTable's function for calculating hash value. 
     * @param [in] key Key to be hashed.
     * @return Calculated hash value.
     */
    uint32_t get_hash(string key);

    /**
     * @brief HTable index range. 
     */
    uint32_t table_size;

    /**
     * @brief C-like array of std::strings.
     */
    string *table;
};


#endif
