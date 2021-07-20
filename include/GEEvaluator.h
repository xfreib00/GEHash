/**
 * @file GEEvaluator.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for GEEvaluator class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "HTable.h"
#include <array>
#include <fstream>
#include <gram/evaluation/Evaluator.h>
#include <gram/individual/Fitness.h>
#include <gram/individual/Phenotype.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

using namespace gram;

/**
 * @brief Class implemeting evaluation mechanism for GEHash.
 */
class GEEvaluator : public Evaluator {

  public:
    /**
     * @brief Default constructor.
     */
    GEEvaluator() = default;

    /**
     * @brief Constructor of GEEvaluator class.
     * @param [in] magic Magic number used in grammar.
     * @param [in] data_path Path to training data file.
     * @param [in] useSum Flag which fitness function to use, if with or without
     * sum.
     */
    GEEvaluator(uint64_t magic, const std::string &data_path,
                const bool &useSum);

    /**
     * @brief Calculate fitness for given program.
     * @param [in] program Generated string containing program.
     * @return Return calculated fitness for given program.
     * @exception If there is duplicity in training data throw hashInsertError
     * exception.
     */
    Fitness calculateFitness(std::string program);

    /**
     * @brief Evaluate given phenotype.
     * @param [in out] phenotype Reference to phenotype to be evaluated.
     * @return Return calculated fitness function. Otherwise set fitness to high
     * number.
     * @exception No exceptions guarantee.
     */
    Fitness evaluate(const Phenotype &phenotype) noexcept override;

    /**
     * @brief Default destructor.
     */
    ~GEEvaluator() = default;

  private:
    /**
     * @brief Instance of HTable used for evaluation of generated phenotype.
     */
    HTable<uint16_t, std::array<uint32_t, 9>> table;

    /**
     * @brief Path to training data file.
     */
    std::string d_path;

    /**
     * @brief Flag if to use fitness with or without sum.
     */
    bool use_sum;

    /**
     * @brief Calculate fitness for given array.
     * @details Auxiliary function used in GEEvaluator::calculateFitness.
     * Function uses formula from research paper by David Grochol and Lukas
     * Sekanina from Brno University of Technology, Faculty of Information
     * Technology called Evolutionary Design of Hash Functions for IPv6 Network
     * Flow Hashing (DOI: 10.1109/CEC48606.2020.9185723). Available
     * <a href="https://ieeexplore.ieee.org/document/9185723">here.</a>
     * @param [in] arr Array representing array dimensions (number of keys
     * mapped to each index).
     * @param [in out] fit Reference to Fitness variable where will be stored
     * result.
     */
    void fitnessWithSum(
        const std::array<uint16_t, numeric_limits<uint16_t>::max()> &arr,
        Fitness &fit);

    /**
     * @brief Calculate fitness from given array.
     * @details Auxiliary function used in GEEvaluator::calculateFitness.
     * Function uses similar formula as GEEvaluator::fitnessWithSum, but fitness
     * is computed as sum of number of keys at each index squared, given that
     * number of keys is greater than 1.
     * @param [in] arr Array representing array dimensions (number of keys
     * mapped on each index).
     * @param [in out] fit Reference to Fitness variable where will be stored
     * result.
     */
    void fitnessWithoutSum(
        const std::array<uint16_t, numeric_limits<uint16_t>::max()> &arr,
        Fitness &fit);

    /**
     * @brief Private function for spliting strings.
     * @details Because std::string has no standard function for splitting
     * strings each project needs to implement its own version. Function used in
     * this project is from answer found at <a
     * href="https://stackoverflow.com/a/37454181">StackOverflow</a>.
     * @param [in] str String to be parsed.
     * @param [in] delim Delimiter used for splitting given string.
     * @return Returns vector of strings.
     */
    std::vector<std::string> split(const std::string &str,
                                   const std::string &delim);
};