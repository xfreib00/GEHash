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
#include <filesystem>
#include <gram/evaluation/Evaluator.h>
#include <gram/individual/Fitness.h>
#include <gram/individual/Phenotype.h>
#include <gram/language/mapper/ContextFreeMapper.h>

namespace GEHash {

/**
 * @brief Class implementing evaluation mechanism for GEHash.
 *
 * @details Class implements phenotype evaluation mechanism for GEHash using
 * gram::Evaluator API. Two main methods used for evaluation are
 * calculateFitness and evaluate which are overridden methods from
 * gram::Evaluator class.
 */
class GEEvaluator : public gram::Evaluator {

  public:
    /**
     * @brief Default constructor.
     */
    GEEvaluator() = default;

    /**
     * @brief Constructor of GEEvaluator class.
     *
     * @param [in] magic Magic number used in grammar.
     * @param [in] data_path Path to training data file.
     * @param [in] useSum Flag which fitness function to use, if with or without
     * sum.
     */
    GEEvaluator(uint64_t magic, const std::filesystem::path &data_path,
                const bool &useSum);

    /**
     * @brief Calculate fitness for given program.
     *
     * @param [in] program Generated string containing program.
     * @return Return calculated fitness for given program.
     * @exception If there is duplicity in training data throw hashInsertError
     * exception.
     */
    gram::Fitness calculateFitness(const std::string &program);

    /**
     * @brief Evaluate given phenotype.
     *
     * @param [in out] phenotype Reference to phenotype to be evaluated.
     * @return Return calculated fitness function. Otherwise set fitness to high
     * number.
     * @exception No exceptions guarantee.
     */
    gram::Fitness
    evaluate(const gram::Phenotype &phenotype) noexcept override final;

    /**
     * @brief Get path to training data file.
     *
     * @return fs::path Return path to training data file.
     */
    std::filesystem::path getDataPath(void) const;

    /**
     * @brief Get flag which determines used fitness function.
     *
     * @return true fitnessWithSum function will be used to evaluate phenotype.
     * @return false fitnessWithoutSum function will be used to evaluate
     * phenotype.
     */
    bool getSumFlag(void) const;

    /**
     * @brief Get reference to constant HTable object.
     *
     * @tparam T Data type specifying range of hash table indexes.
     * @tparam V Data type of records.
     * @return const HTable<T, V>>& Reference to constant HTable object.
     */
    template <typename T, typename V> const HTable<T, V> &getTable(void) const;

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
    std::filesystem::path d_path;

    /**
     * @brief Flag if to use fitness with or without sum.
     */
    bool use_sum;

    /**
     * @brief Calculate fitness for given array.
     *
     * @details Auxiliary function used in GEEvaluator::calculateFitness.
     * Function uses formula from research paper by David Grochol and Lukas
     * Sekanina from Brno University of Technology, Faculty of Information
     * Technology called Evolutionary Design of Hash Functions for IPv6 Network
     * Flow Hashing (DOI: 10.1109/CEC48606.2020.9185723). Available
     * <a href="https://ieeexplore.ieee.org/document/9185723">here.</a>
     * @tparam T Data type used in array.
     * @tparam V Size of array.
     * @param [in] arr Array representing array dimensions (number of keys
     * mapped to each index).
     * @param [in out] fit Reference to Fitness variable where will be stored
     * result.
     */
    template <typename T, std::size_t V>
    void fitnessWithSum(const std::array<T, V> &arr, gram::Fitness &fit);

    /**
     * @brief Calculate fitness from given array.
     *
     * @details Auxiliary function used in GEEvaluator::calculateFitness.
     * Function uses similar formula as GEEvaluator::fitnessWithSum, but fitness
     * is computed as sum of number of keys at each index squared, given that
     * number of keys is greater than 1.
     * @tparam T Data type used in array.
     * @tparam V Size of array.
     * @param [in] arr Array representing array dimensions (number of keys
     * mapped on each index).
     * @param [in out] fit Reference to Fitness variable where will be stored
     * result.
     */
    template <typename T, std::size_t V>
    void fitnessWithoutSum(const std::array<T, V> &arr, gram::Fitness &fit);
};

} // namespace GEHash