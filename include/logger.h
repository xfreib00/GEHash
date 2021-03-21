/**
 * @file logger.h
 * @author Adam Freiberg
 * @brief Header file for Logger class
 */

#ifndef GEHASH_LOGGER
#define GEHASH_LOGGER

#include <chrono>
#include <stdexcept>
#include <fstream>
#include <gram/population/Population.h>
#include <gram/util/logger/Logger.h>

using namespace gram;

/**
 * @brief Logger class for GEHash grammatical evolution.
 */
class GELogger : public Logger{

public:

    /**
	 * @brief Default constructor of Logger class.
	 */
    GELogger() = default;

	/**
	 * @brief Parameterized constructor of Logger class.
     * @param [in] path Reference to path to output file.
	 */
	GELogger(const std::string& path);
	
	/**
	 *	@brief Log progress of current evolution run.
	 *	@param [in] population Reference population object.
	 */
	void logProgress(const Population& population);

	/**
	 * @brief Log result of evolution run.
	 * @param [in] population Reference population object.
	 */
	void logResult(const Population& population);

	/**
	 * @brief Logger class destructor.
	 */
	~GELogger();

private:

	/**
	 * @brief Fstream variable for Logger output file. 
	 */
	std::fstream out;

};
#endif