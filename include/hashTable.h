/**
 * @file hashTable.h
 * @author Adam Freiberg
 * @brief Header file for HTable class
 */

#pragma once

#include "error/hashError.h"
#include <array>
#include <chaiscript/chaiscript.hpp>
#include <limits>
#include <string>
#include <vector>

using namespace std;
using namespace chaiscript;

/**
 * @brief Class implementing basic hash table.
 * @tparam T Data type specifying range of hash table indexes.
 * @tparam V Data type of records.
 */
template <typename T, typename V, typename = enable_if_t<is_integral<T>::value>>
class HTable {

  public:
    /**
     * @brief HTable constructor.
     */
    HTable() = default;

    /**
     * @brief Insert element to table.
     * @param [in] key Key to be inserted to table.
     * @exception If key is already in table hashInsertError exception is
     * thrown.
     */
    void Insert(V key) {
        /*if (T hash = get_hash(key); table[hash].empty()) {
            table[hash].push_back(key);
        } else {
            auto it = table[hash].begin();

            for (; it != table[hash].end();) {
                if (*it == key) {
                    throw hashInsertError();
                } else {
                    it++;
                }
            }
            table[hash].push_back(key);
        }*/

        /* use simple push_back to find out how many keys will be mapped to
         * single index */
        T hash = get_hash(key);
        table[hash].push_back(key);
    };

    /**
     * @brief Remove element from table.
     * @param [in] key Key to be removed from table.
     * @exception If key is not in table hashRemoveError exception is thrown.
     */
    void Remove(V key) {
        T hash = get_hash(key);
        if (table[hash].empty()) {
            throw hashRemoveError();
        }

        auto it = table[hash].begin();

        for (; it != table[hash].end();) {
            if (*it == key) {
                it = table[hash].erase(it);
                break;
            } else {
                it++;
            }
        }
        if (it == table[hash].end()) {
            throw hashRemoveError();
        }
    };

    /**
     * @brief Find key in table.
     * @param [in] key Key to be found in table.
     * @return Return index if search was successful. Throw exception otherwise.
     * @exception If key is not in table hashSearchError exception is thrown.
     */
    T Search(V key) {
        T hash = get_hash(key);
        if (table[hash].empty()) {
            throw hashSearchError();
        }

        auto it = table[hash].begin();

        for (; it != table[hash].end();) {
            if (*it == key) {
                return hash;
            } else {
                it++;
            }
        }

        throw hashSearchError();
    };

    /**
     * @brief Set function to be evaluated and used in calculating hash value.
     * @param [in] f String representation of generated function.
     */
    void setFunc(string f) { func = f; };

    /**
     * @brief Set magic number used in calculating hash value.
     * @param [in] m Value to be assigned to magic number.
     */
    void setMagic(uint64_t m) { magic_num = m; };

    /**
     * @brief Get the size of table
     *
     * @return constexpr T Size of table
     */
    constexpr size_t getSize(void) const { return table.size(); };

    /**
     * @brief Function fills given array with element count
     * at each index of hash table.
     * @return Array filled with elemenent count for each index of HTable.
     */
    array<T, numeric_limits<T>::max()> getDimensions(void) {
        array<T, numeric_limits<T>::max()> arr;
        for (size_t i = 0; i < table.size(); i++) {
            arr[i] = static_cast<T>(table[i].size());
        }
        return arr;
    };

    /**
     * @brief Clear table indexes.
     * @throw Noexcept is quaranteed.
     */
    void clearTab(void) noexcept {
        for (auto &i : table) {
            i.clear();
        }
    };

    /**
     * @brief HTable destructor.
     */
    ~HTable() = default;

  private:
    /**
     * @brief HTable's function for calculating hash value.
     * @param [in] key Key to be hashed.
     * @return Calculated hash value.
     * @exception If no function was not set by HTable::setFunc
     * or given string was empty, throw hashFuncError exception.
     * If Lua evaluation fails, throw hashLuaError exception.
     */
    T get_hash(V key) {
        if (func.empty()) {
            throw hashFuncError();
        }

        /* initial value of hash */
        uint64_t hash = 0;

        /* push magic_num as constant to chaiScript engine */
        chai.add(const_var(magic_num), "magic");

        /* push initial hash value to engine to be used in iterations */
        chai.add(var(hash), "hash");

        for (auto &k : key) {
            /* push current value of key to engine */
            chai.add(const_var(k), "key");

            /* return new hash value for each loop */
            hash = chai.eval<uint64_t>(func);
        }

        /* use xor-folding if needed to return hash value in specified range */
        switch (sizeof(T)) {
        case 2:
            return static_cast<T>((((hash >> (sizeof(T) * 8)) ^ hash) &
                                   (((static_cast<T>(1) << (sizeof(T) * 8)) -
                                     static_cast<T>(1)))));
            break;
        case 4:
            return static_cast<T>(
                (hash >> (sizeof(T) * 8)) ^
                (hash & (((static_cast<T>(1) << (sizeof(T) * 8)) -
                          static_cast<T>(1)))));
        default:
            return static_cast<T>(hash);
            break;
        }
    };

    /**
     * @brief Table alocated using std::array
     */
    array<vector<V>, numeric_limits<T>::max()> table;

    /**
     * @brief ChaiScript class object.
     */
    ChaiScript chai;

    /**
     * @brief Magic number used in calculating hash value.
     */
    uint64_t magic_num = 0;

    /**
     * @brief String containing generated hash function.
     */
    string func;
};
