/**
 * @file GEEvaluator.cpp
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Source file for GEEvaluator class methods
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "GEEvaluator.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

/**
 * @brief Splitting strings by chosen delimiter.
 *
 * @details Because std::string has no standard function for splitting
 * strings each project needs to implement its own version. Function used in
 * this project is from answer found at <a
 * href="https://stackoverflow.com/a/37454181">StackOverflow</a>.
 * @param [in] str String to be parsed.
 * @param [in] delim Delimiter used for splitting given string.
 * @return Returns vector of strings.
 */
static std::vector<std::string> split(const std::string &str,
                                      const std::string &delim) {
    std::vector<std::string> chunks;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            chunks.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return chunks;
}

namespace GEHash {

/**
 * @brief Using fs identifier instead of std::filesystem to shorten code.
 */
namespace fs = std::filesystem;

GEEvaluator::GEEvaluator(uint64_t magic, const fs::path &data_path,
                         const bool &useSum)
    : d_path{data_path}, use_sum{useSum} {
    table.setMagic(magic);
}

gram::Fitness GEEvaluator::calculateFitness(const std::string &program) {
    gram::Fitness fit = 0.0;

    /* set up table for */
    table.setFunc(program);

    std::array<uint16_t, std::numeric_limits<uint16_t>::max()> arr;
    std::array<uint32_t, 9> keys;
    std::vector<std::string> chunks;

    /* open file containing train data */
    std::ifstream f(d_path);

    /* insert training data to hash table */
    for (std::string line; getline(f, line);) {

        chunks = split(line, ";");

        for (auto it = 0ul; it < keys.size(); it++) {
            if (it > 7) {
                keys[it] = static_cast<uint32_t>(std::stoul(chunks[it]));
                keys[it] = keys[it] << 16;
                keys[it] |= static_cast<uint32_t>(std::stoul(chunks[it + 1]));
                break;
            }
            keys[it] = static_cast<uint32_t>(std::stoul(chunks[it]));
        }

        try {
            table.Insert(keys);
            std::fill_n(keys.begin(), keys.size(), 0);
        } catch (GEHashError::hashInsertError &e) {
            table.clear();
            throw;
        }
    }

    /* get counts at each index */
    arr = table.getDimensions();

    if (use_sum) {
        fitnessWithSum(arr, fit);
    } else {
        fitnessWithoutSum(arr, fit);
    }

    table.clear();

    return fit;
}

gram::Fitness GEEvaluator::evaluate(const gram::Phenotype &phenotype) noexcept {
    try {
        return calculateFitness(phenotype);
    } catch (GEHashError::hashInsertError &e) {
        std::cerr << "Duplicity in training data: " << e.what() << std::endl;
        return std::numeric_limits<gram::Fitness>::max();
    } catch (std::exception &e) {
        std::cerr << e.what() << ": " << phenotype << std::endl;
        return std::numeric_limits<gram::Fitness>::max();
    }
}

template <typename T, std::size_t V>
void GEEvaluator::fitnessWithSum(const std::array<T, V> &arr,
                                 gram::Fitness &fit) {

    /* temporary fitness sum */
    gram::Fitness temp = 0.0;

    /* calculate fitness as sum of current + previous values, greater than 1,
     * squared */
    std::for_each(arr.begin(), arr.end(), [&](const auto &a) {
        if (a > 1) {
            temp += std::pow(a, 2);
            fit += temp;
        }
    });
}

template <typename T, std::size_t V>
void GEEvaluator::fitnessWithoutSum(const std::array<T, V> &arr,
                                    gram::Fitness &fit) {

    /* calculate fitness as sum of values, greater than 1, squared */
    std::for_each(arr.begin(), arr.end(), [&](const auto &a) {
        if (a > 1) {
            fit += std::pow(a, 2);
        }
    });
}

fs::path GEEvaluator::getDataPath(void) const { return d_path; }

bool GEEvaluator::getSumFlag(void) const { return use_sum; }

template <typename T, typename V>
const HTable<T, V> &GEEvaluator::getTable(void) const {
    return table;
};

} // namespace GEHash