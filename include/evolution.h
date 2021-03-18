/**
 * @file evolution.h
 * @author Adam Freiberg
 * @brief Header file for GEHash class
 */

#ifndef GEHASH_EVO
#define GEHASH_EVO

#include <chrono>
#include <stdexcept>
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
#include <random>
#include "logger.h"
#include "driver.h"

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
	 */
	void SetDriver();

	/**
	 * @brief Method for running evolution algorithm.
	 */
	void Run(void);
	
	/**
	 * @brief Virutal destructor.
	 */
	virtual ~GEHash() = default;

private:
	/**
	 * @brief Internal parameter for number of individuals in population. 
	 */
	unsigned long p;
	/**
	 * @brief Internal parameter for maximum number of generations. 
	 */
	unsigned long g;

	/**
	 * @brief Unique pointer to Logger object.
	 */
	std::unique_ptr<GELogger> log;

	BnfRuleParser parser;
	
	std::unique_ptr<ContextFreeGrammar> gramm;
	
	std::unique_ptr<ContextFreeMapper> cfm;

	std::unique_ptr<GEDriver> driver;
};
#endif