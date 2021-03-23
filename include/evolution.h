/**
 * @file evolution.h
 * @author Adam Freiberg
 * @brief Header file for GEHash class
 */

#ifndef GEHASH_EVO
#define GEHASH_EVO

/* include gram headers */
#include <gram/Evolution.h>
#include <gram/language/parser/BnfRuleParser.h>
#include <gram/operator/selector/TournamentSelector.h>
#include <gram/operator/selector/comparer/LowFitnessComparer.h>
#include <gram/operator/crossover/OnePointCrossover.h>
#include <gram/random/Probability.h>
#include <gram/operator/mutation/BernoulliStepGenerator.h>
#include <gram/operator/mutation/CodonMutation.h>
#include <gram/population/reproducer/PassionateReproducer.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/population/initializer/RandomInitializer.h>
#include <gram/random/number_generator/StdNumberGenerator.h>
#include <gram/evaluation/driver/SingleThreadDriver.h>
#include <gram/evaluation/EvaluatorCache.h>

/* standard libraries and user defined dependencies */
#include <stdexcept>
#include <random>
#include <functional>
#include "logger.h"
#include "driver.h"

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
	 * @param [in] generation Maximum number of generations. Must be more than 2.
	 * @param [in] population Number of individuals in population. Must be more than 50.
	 * @param [in out] outpath Path to output file used by Logger class.
	 * @exception If any of function arguments are invalid, throw std::invalid_argument exception.
	 */
	GEHash(unsigned long generation, unsigned long population,
	std::string& outpath);
	
	/**
	 * @brief Setter for grammar parser.
	 * @param [in out] grammar Grammar in BNF form.
	 * @param [in] limit Max number of wrapping operations.
	 * @throw If grammar is empty string throw std::invalid_argument exception.
	 */
	void SetGrammar(std::string& grammar, unsigned long limit);

	/**
	 * @brief Setter for evaluation driver.
	 * @param [in] magic Magic number used in grammar.
	 */
	void SetEvaluator(unsigned long magic);

	/**
	 * @brief Method for running evolution algorithm.
	 */
	void Run(void);
	
	/**
	 * @brief Default destructor.
	 */
	virtual ~GEHash() = default;

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
	 * @brief Unique pointer to GEDriver object.
	 */
	std::unique_ptr<GEDriver> eval;

	/**
	 * @brief Unique pointer to gram::EvaluatorCache object.
	 */
	std::unique_ptr<EvaluatorCache> cache;
	
	/**
	 * @brief Unique pointer to gram::SingleThreadDriver object.
	 */
	std::unique_ptr<SingleThreadDriver> driver;
};

#endif