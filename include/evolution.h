/**
 * @file evolution.h
 * @author Adam Freiberg
 * @brief Header file for GEHash class
 */

#include <chrono>
#include <stdexcept>
#include <gram/Evolution.h>

class GEHash {

public:
	/**
	 * @brief Constructor of GEHash class.
	 * @param [in] Maximum number of generations.
	 * @param [in] Number of individuals in population.
	 */
	GEHash(unsigned long generation, unsigned long population);
	
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
};
