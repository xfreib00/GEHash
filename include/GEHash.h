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

/* standard libraries and user defined dependencies */
#include "GEEvaluator.h"
#include "GEEvolution.h"
#include "GELogger.h"
#include "error/geError.h"
#include <functional>
#include <random>
#include <stdexcept>

/**
 * @brief Main class for creating new hash functions
 * using grammatical evolution.
 * @details Wrapper class utilizing gram library for grammatical evolution.
 */
class GEHash {

  public:
    GEHash() = delete;

    /**
     * @brief Constructor of GEHash class.
     * @param [in] generation Maximum number of generations. Must be more
     * than 2.
     * @param [in] population Number of individuals in population. Must be more
     * than 10.
     * @exception geGenerationError Generation number is out of range.
     * @exception gePopulationError Population number is out of range.
     */
    GEHash(unsigned long generation, unsigned long population);

    /**
     * @brief Setter for GELogger class.
     * @param [in out] outpath Path to output file used by Logger class.
     * @param [in] debug Use debugging in logger, that additionaly outputs
     * phenotype. Defaluts to false.
     */
    void SetLogger(const std::string &outpath, bool debug = false);

    /**
     * @brief Setter for grammar parser.
     * @param [in out] grammar Grammar in BNF form.
     * @param [in] limit Max number of wrapping operations.
     * @exception geGrammarError Given grammar string is empty.
     */
    void SetGrammar(std::string &grammar, unsigned long limit);

    /**
     * @brief Setter for evaluation driver.
     * @param [in] magic Magic number used in grammar.
     * @param [in] data_path Path to training data file.
     * @param [in] useSum Flag which fitness function to use, if with or without
     * sum.
     */
    void SetEvaluator(unsigned long magic, const std::string &data_path,
                      const bool &useSum);

    /**
     * @brief Set the tournament size
     *
     * @param size Number of individuals in tournament.
     * @exception geTournamentError Number of individuals is out of range.
     */
    void SetTournament(unsigned long size);

    /**
     * @brief Set mutation probability.
     *
     * @param probability Mutation probability.
     * @exception geMutationError Probability is not in range.
     */
    void SetProbability(double probability);

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
     * @brief Number of individuals in population.
     */
    unsigned long p;
    /**
     * @brief Maximum number of generations.
     */
    unsigned long g;

    /**
     * @brief Tournament size.
     *
     */
    unsigned long t_size;

    /**
     * @brief Mutation probability.
     */
    double m_prob;

    /**
     * @brief Unique pointer to GELogger object.
     */
    std::unique_ptr<GELogger> log;

    /**
     * @brief Instance of gram::BnfRuleParser.
     */
    BnfRuleParser parser;

    /**
     * @brief Unique pointer to gram::ContextFreeGramar object.
     */
    std::unique_ptr<ContextFreeGrammar> gramm;

    /**
     * @brief Unique pointer to gram::ContextFreeMapper object.
     */
    std::unique_ptr<ContextFreeMapper> cfm;

    /**
     * @brief Unique pointer to gram::ContextFreeMapper object used in GELogger
     * class.
     */
    std::unique_ptr<ContextFreeMapper> cfmLogger;

    /**
     * @brief Unique pointer to GEEvaluator object.
     */
    std::unique_ptr<GEEvaluator> eval;

    /**
     * @brief Unique pointer to gram::EvaluatorCache object.
     */
    std::unique_ptr<EvaluatorCache> cache;

    /**
     * @brief Unique pointer to gram::SingleThreadDriver object.
     */
    std::unique_ptr<SingleThreadDriver> driver;
};