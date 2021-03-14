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
#include "logger.h"

class GEHash {

public:
	/**
	 * @brief Constructor of GEHash class.
	 * @param [in] generation Maximum number of generations.
	 * @param [in] population Number of individuals in population.
	 * @param [in out] outpath Path to output file used by Logger class.
	 */
	GEHash(unsigned long generation, unsigned long population,
	std::string &outpath);
	
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
};
#endif