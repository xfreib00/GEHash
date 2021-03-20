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

using namespace std;

template <typename T>
class HTable {

public:

    /**
     * @brief HTable constructor.
     */
    HTable() = default;

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
     * @brief Default HTable destructor. 
     */
    ~HTable() = default;

private:

    /**
     * @brief HTable's function for calculating hash value. 
     * @param [in] key Key to be hashed.
     * @return Calculated hash value.
     */
    T get_hash(string key);

    /**
     * @brief HTable index range. 
     */
    T table_size;

    /**
     * @brief Table alocated using std::array
     */
    array<T,numeric_limits<T>::max()> table;
};


#endif
