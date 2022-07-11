/**
 * @file HTable.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for HTable class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "error/hashError.h"
#include <algorithm>
#include <array>
#include <chaiscript/chaiscript.hpp>
#include <initializer_list>
#include <limits>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace GEHash {

/**
 * @brief Class implementing basic hash table.
 *
 * @details Class is set up as hash table with customizable hash function,
 * allowing us to dynamically change hash function when needed. Hash function is
 * provided in form of string via setFunc function. Implicitly table has no hash
 * function.
 * @tparam T Data type specifying range of hash table indexes.
 * @tparam V Data type of records.
 */
template <typename T, typename V,
          typename = std::enable_if_t<std::is_unsigned_v<T>>>
class HTable {

    /**
     * @brief Typedef table_t for better readability.
     */
    typedef std::array<std::vector<V>, std::numeric_limits<T>::max()> table_t;

  public:
    /**
     * @brief Alias for const_iterator taken from table_t type.
     */
    using const_iterator = typename table_t::const_iterator;

    /**
     * @brief Alias for const_reference taken from table_t type.
     */
    using const_reference = typename table_t::const_reference;

  public:
    /**
     * @brief Default HTable constructor.
     */
    HTable() = default;

    /**
     * @brief Construct a new HTable object
     *
     * @param [in] function String representing hash function.
     */
    explicit HTable(const std::string &function) : func{function} {}

    /**
     * @brief Construct a new HTable object
     *
     * @param [in] function String representing hash function.
     * @param [in] list Initializer list of values to be inserted to table.
     */
    HTable(const std::string &function, std::initializer_list<V> list)
        : func{function} {
        for (auto &l : list) {
            Insert(l);
        }
    };

    /**
     * @brief HTable's iterator pointing to the table's begin.
     *
     * @details Usually containers implement two instances of begin iterator
     * which will return an iterator or a const_iterator depending on the
     * const-qualification of the object it is called on. HTable implements only
     * const_iterator version, because data manipulation is allowed only via
     * class member functions.
     * @return const_iterator Iterator to the first element.
     */
    constexpr const_iterator begin() const noexcept { return table.begin(); }

    /**
     * @brief HTable's iterator pointing to the element following the last
     * element.
     *
     * @details Usually containers implement two instances of end iterator
     * which will return an iterator or a const_iterator depending on the
     * const-qualification of the object it is called on. HTable implements only
     * const_iterator version, because data manipulation is allowed only via
     * class member functions.
     * @return const_iterator Iterator to the element following the last
     * element.
     */
    constexpr const_iterator end() const noexcept { return table.end(); }

    /**
     * @brief HTable's constant iterator pointing to the table's begin.
     *
     * @return const_iterator Constant iterator to the first element.
     */
    constexpr const_iterator cbegin() const noexcept { return table.cbegin(); }

    /**
     * @brief HTable's constant iterator pointing to the element following the
     * last element.
     *
     * @return const_iterator Constant iterator to the element following the
     * last element.
     */
    constexpr const_iterator cend() const noexcept { return table.cend(); }

    /**
     * @brief Returns a reference to the element at specified location index. No
     * bounds checking is performed.
     *
     * @param [in] index Position of the element to return.
     * @return const_reference Constant reference to the requested element.
     */
    constexpr const_reference operator[](const size_t index) const {
        return table[index];
    }

    /**
     * @brief Returns a reference to the element at specified location pos,
     * with bounds checking.
     *
     * @param [in] index Position of the element to return.
     * @exception std::out_of_range If pos is not within the range of the
     * container, an exception of type std::out_of_range is thrown.
     * @return const_reference Constant reference to the requested element.
     */
    constexpr const_reference at(const size_t index) const {
        return table.at(index);
    }

    /**
     * @brief Insert element to table.
     *
     * @param [in] key Key to be inserted to table.
     * @exception If key is already in table hashInsertError exception is
     * thrown.
     */
    void Insert(V key) {

        if (T hash = get_hash(key); table[hash].empty()) {
            table[hash].push_back(key);
        } else {
            auto it = table[hash].begin();

            for (; it != table[hash].end();) {
                if (*it == key) {
                    throw GEHashError::hashInsertError();
                } else {
                    it++;
                }
            }
            table[hash].push_back(key);
        }
    };

    /**
     * @brief Remove element from table.
     *
     * @param [in] key Key to be removed from table.
     * @exception If key is not in table hashRemoveError exception is thrown.
     */
    void Remove(V key) {

        bool removed = false;

        if (T hash = get_hash(key); table[hash].empty()) {
            throw GEHashError::hashRemoveError();
        } else {
            auto it = table[hash].begin();

            for (; it != table[hash].end();) {
                if (*it == key) {
                    it = table[hash].erase(it);
                    removed = true;
                    break;
                } else {
                    it++;
                }
            }
        }
        if (!removed) {
            throw GEHashError::hashRemoveError();
        }
    };

    /**
     * @brief Find key in table.
     *
     * @param [in] key Key to be found in table.
     * @return Return index if search was successful. Throw exception otherwise.
     * @exception If key is not in table hashSearchError exception is thrown.
     */
    T Search(V key) {

        if (T hash = get_hash(key); table[hash].empty()) {
            throw GEHashError::hashSearchError();
        } else {
            auto it = table[hash].begin();

            for (; it != table[hash].end();) {
                if (*it == key) {
                    return hash;
                } else {
                    it++;
                }
            }
        }

        throw GEHashError::hashSearchError();
    };

    /**
     * @brief Set function to be evaluated and used in calculating hash value.
     *
     * @param [in] f String representation of generated function.
     */
    void setFunc(const std::string &f) { func = f; };

    /**
     * @brief Set magic number used in calculating hash value.
     *
     * @param [in] m Value to be assigned to magic number.
     */
    void setMagic(uint64_t m) { magic_num = m; };

    /**
     * @brief Get the size of table
     *
     * @return size_t T Size of table
     */
    constexpr size_t getSize(void) const { return table.size(); };

    /**
     * @brief Get used hash function.
     *
     * @return std::string Hash function. If not set empty string is returned.
     */
    std::string getFunc(void) const { return func; };

    /**
     * @brief Get magic number used in calculating hash value.
     *
     * @return std::optional<uint64_t> If *this contains a value, returns a
     * reference to the contained value. Otherwise, throws a
     * std::bad_optional_access exception.
     */
    std::optional<uint64_t> getMagic(void) const { return magic_num; };

    /**
     * @brief Function fills given array with element count
     * at each index of hash table.
     *
     * @deprecated Function is used as helper function for fitness evaluation.
     * After implementation of iterators this function is unnecessary. Will be
     * removed in version 1.3.0.
     * @return Array filled with element count for each index of HTable.
     */
    [[deprecated("Use class iterators instead.")]] std::array<
        T, std::numeric_limits<T>::max()>
    getDimensions(void) {
        std::array<T, std::numeric_limits<T>::max()> arr;
        for (size_t i = 0; i < table.size(); i++) {
            arr[i] = static_cast<T>(table[i].size());
        }
        return arr;
    };

    /**
     * @brief Clear table indexes.
     *
     * @throw Noexcept is guaranteed.
     */
    void clear(void) noexcept {
        std::for_each(table.begin(), table.end(), [](auto &i) { i.clear(); });
    };

    /**
     * @brief HTable destructor.
     */
    ~HTable() = default;

  private:
    /**
     * @brief HTable's function for calculating hash value.
     *
     * @param [in] key Key to be hashed.
     * @return Calculated hash value.
     * @exception If no function was not set by HTable::setFunc
     * or given string was empty, throw hashFuncError exception.
     * If ChaiScript evaluation fails, throws internal ChaiScript exception.
     */
    [[nodiscard]] T get_hash(V key) {
        if (func.empty()) {
            throw GEHashError::hashFuncError();
        }

        /* initial value of hash */
        uint64_t hash = 0;

        if (magic_num) {
            /* push magic_num as constant to chaiScript engine */
            chai.add(chaiscript::const_var(magic_num.value()), "magic");
        }

        /* push initial hash value to engine to be used in iterations */
        chai.add(chaiscript::var(hash), "hash");

        /* push current value of key to engine */
        chai.add(chaiscript::const_var(key), "key");

        /* calculate hash value */
        hash = chai.eval<uint64_t>(func);

        /* use xor-folding if needed to return hash value in specified range */
        if constexpr (sizeof(T) == 2) {
            return static_cast<T>((((hash >> (sizeof(T) * 8)) ^ hash) &
                                   (((static_cast<T>(1) << (sizeof(T) * 8)) -
                                     static_cast<T>(1)))));
        }
        if constexpr (sizeof(T) == 4) {
            return static_cast<T>(
                (hash >> (sizeof(T) * 8)) ^
                (hash & (((static_cast<T>(1) << (sizeof(T) * 8)) -
                          static_cast<T>(1)))));
        }

        return static_cast<T>(hash);
    };

    /**
     * @brief Table allocated using std::array
     */
    table_t table;

    /**
     * @brief ChaiScript class object.
     */
    chaiscript::ChaiScript chai;

    /**
     * @brief Magic number used in calculating hash value.
     */
    std::optional<uint64_t> magic_num;

    /**
     * @brief String containing generated hash function.
     */
    std::string func{};
};

} // namespace GEHash