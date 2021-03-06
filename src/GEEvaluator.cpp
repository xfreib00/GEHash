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

GEEvaluator::GEEvaluator(uint64_t magic, const std::string &data_path,
                         const bool &useSum) {
    table.setMagic(magic);
    d_path = data_path;
    use_sum = useSum;
}

Fitness GEEvaluator::calculateFitness(std::string program) {
    Fitness fit = 0.0;

    /* set up table for */
    table.setFunc(program);

    std::array<uint16_t, numeric_limits<uint16_t>::max()> arr;
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
        } catch (hashInsertError &e) {
            // std::cerr << line << '\n';
            table.clearTab();
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

    table.clearTab();

    return fit;
}

Fitness GEEvaluator::evaluate(const Phenotype &phenotype) noexcept {
    try {
        return calculateFitness(phenotype);
    } catch (hashInsertError &e) {
        std::cerr << "Duplicity in training data: " << e.what() << std::endl;
        return numeric_limits<Fitness>::max();
    } catch (std::exception &e) {
        std::cerr << e.what() << ": " << phenotype << std::endl;
        return numeric_limits<Fitness>::max();
    }
}

std::vector<std::string> GEEvaluator::split(const std::string &str,
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

void GEEvaluator::fitnessWithSum(
    const std::array<uint16_t, numeric_limits<uint16_t>::max()> &arr,
    Fitness &fit) {

    /* temporary fitness sum */
    Fitness temp = 0.0;

    /* calculate fitness as sum of current + previous values, greater than 1,
     * squared */
    for (auto &a : arr) {
        if (a > 1) {
            temp += std::pow(a, 2);
            fit += temp;
        }
    }
}

void GEEvaluator::fitnessWithoutSum(
    const std::array<uint16_t, numeric_limits<uint16_t>::max()> &arr,
    Fitness &fit) {

    /* calculate fitness as sum of values, greater than 1, squared */
    for (auto &a : arr) {
        if (a > 1) {
            fit += pow(a, 2);
        }
    }
}