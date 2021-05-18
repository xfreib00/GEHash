/**
 * @file evaluator.cpp
 * @author Adam Freiberg
 * @brief Source file for GEEvaluator class methods
 */

#include "evaluator.h"

GEEvaluator::GEEvaluator(uint64_t magic, const std::string &data_path) {
    table.setMagic(magic);
    d_path = data_path;
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
        } catch (hashInsertError &e) {
            table.clearTab();
            throw;
        }
    }

    /* get counts at each index */
    arr = table.getDimensions();

    /* calculate fitness as weighted  */
    for (auto &a : arr) {
        if (a > 1) {
            fit += pow(a, 2);
        }
    }

    table.clearTab();

    return fit;
}

Fitness GEEvaluator::evaluate(const Phenotype &phenotype) noexcept {
    try {
        return calculateFitness(phenotype);
    } catch (hashInsertError &e) {
        std::cerr << "Duplicity in training data: " << e.what() << std::endl;
        return 100000.0;
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