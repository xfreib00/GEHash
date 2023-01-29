/**
 * @file GEHash.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for GEHash class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

/* include gram headers */

#include <gram/Evolution.h>
#include <gram/evaluation/EvaluatorCache.h>
#include <gram/evaluation/driver/SingleThreadDriver.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/operator/crossover/OnePointCrossover.h>
#include <gram/operator/mutation/BernoulliStepGenerator.h>
#include <gram/operator/mutation/CodonMutation.h>
#include <gram/operator/selector/TournamentSelector.h>
#include <gram/operator/selector/comparer/LowFitnessComparer.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/population/reproducer/PassionateReproducer.h>
#include <gram/random/Probability.h>
#include <gram/random/number_generator/StdNumberGenerator.h>

/* user defined dependencies */
#include "GEEvaluator.h"
#include "GELogger.h"

/**
 * @brief General namespace for all classes of GEHash project
 */
namespace GEHash {

/**
 * @brief Main class for creating new hash functions
 * using grammatical evolution.
 *
 * @details Class is used as a wrapper for Gram library to set up and run
 * grammatical evolution.
 */
class GEHash {

  public:
    /**
     * @brief Construct a new GEHash object
     */
    GEHash() = default;

    /**
     * @brief Constructor of GEHash class.
     *
     * @param [in] generation Maximum number of generations. Must be more
     * than 2.
     * @param [in] population Number of individuals in population. Must be more
     * than 10.
     * @exception geGenerationError Generation number is out of range.
     * @exception gePopulationError Population number is out of range.
     */
    explicit GEHash(uint64_t generation, uint64_t population);

    /**
     * @brief Setter for GELogger class.
     *
     * @param [in out] outpath Path to output file used by Logger class.
     * @param [in] debug Use debugging in logger, that additionally outputs
     * phenotype. Defaults to false.
     */
    void SetLogger(const std::string &outpath, bool debug = false);

    /**
     * @brief Setter for grammar parser.
     *
     * @param [in out] grammar Grammar in BNF form.
     * @param [in] limit Max number of wrapping operations.
     * @exception geGrammarError Given grammar string is empty.
     */
    void SetGrammar(std::string &grammar, uint64_t limit);

    /**
     * @brief Setter for evaluation driver.
     *
     * @param [in] magic Magic number used in grammar.
     * @param [in] data_path Path to training data file.
     * @param [in] useSum Flag which fitness function to use, if with or without
     * sum.
     */
    void SetEvaluator(uint64_t magic, const std::string &data_path,
                      const bool &useSum);

    /**
     * @brief Set the tournament size
     *
     * @param [in] size Number of individuals in tournament.
     * @exception geTournamentError Number of individuals is out of range.
     */
    void SetTournament(uint64_t size);

    /**
     * @brief Set mutation probability.
     *
     * @param [in] probability Mutation probability.
     * @exception geMutationError Probability is not in range.
     */
    void SetProbability(double probability);

    /**
     * @brief Get tournament size.
     *
     * @return unsigned long Return tournament size. Returns zero when
     * uninitialized.
     */
    constexpr uint64_t GetTournament(void) const;

    /**
     * @brief Get mutation probability. Defaults to zero.
     *
     * @return double Return mutation probability.
     */
    constexpr double GetProbability(void) const;

    /**
     * @brief Get size of population.
     *
     * @return unsigned long Return population size. Returns zero when
     * uninitialized.
     */
    constexpr uint64_t GetPopulation(void) const;

    /**
     * @brief Get number of generations.
     *
     * @return unsigned long Return number of generations. Returns zero when
     * uninitialized.
     */
    constexpr uint64_t GetGenerations(void) const;

    /**
     * @brief Method for running evolution algorithm.
     */
    void Run(void);

    /**
     * @brief Default destructor.
     */
    ~GEHash() = default;

  private:
    /**
     * @brief Number of individuals in population. Zero when uninitialized.
     */
    uint64_t m_p = 0;

    /**
     * @brief Maximum number of generations. Zero when uninitialized.
     */
    uint64_t m_g = 0;

    /**
     * @brief Tournament size. Zero when uninitialized.
     */
    uint64_t m_t_size = 0;

    /**
     * @brief Mutation probability. Zero when uninitialized.
     */
    double m_prob = 0.0;

    /**
     * @brief Unique pointer to GELogger object.
     */
    std::unique_ptr<GELogger> log;

    /**
     * @brief Instance of gram::BnfRuleParser.
     */
    gram::BnfRuleParser parser;

    /**
     * @brief Unique pointer to gram::ContextFreeGramar object.
     */
    std::unique_ptr<gram::ContextFreeGrammar> gramm;

    /**
     * @brief Unique pointer to gram::ContextFreeMapper object.
     */
    std::unique_ptr<gram::ContextFreeMapper> cfm;

    /**
     * @brief Unique pointer to gram::ContextFreeMapper object used in GELogger
     * class.
     */
    std::unique_ptr<gram::ContextFreeMapper> cfmLogger;

    /**
     * @brief Unique pointer to GEEvaluator object.
     */
    std::unique_ptr<GEEvaluator> eval;

    /**
     * @brief Unique pointer to gram::EvaluatorCache object.
     */
    std::unique_ptr<gram::EvaluatorCache> cache;

    /**
     * @brief Unique pointer to gram::SingleThreadDriver object.
     */
    std::unique_ptr<gram::SingleThreadDriver> driver;
};

} // namespace GEHash