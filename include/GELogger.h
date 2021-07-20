/**
 * @file GELogger.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for GELogger class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "error/loggerError.h"
#include <fstream>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/population/Population.h>
#include <gram/util/logger/Logger.h>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using namespace gram;
using namespace std;

/**
 * @brief Logger class for GEHash grammatical evolution.
 */
class GELogger : public Logger {

  public:
    /// Nlohmann::json type
    using json = nlohmann::json;

    /**
     * @brief Default constructor of Logger class.
     */
    GELogger() = default;

    /**
     * @brief Parameterized constructor of Logger class.
     * @param [in] path Reference to path to output file.
     * @param [in] logMapper Unique pointer to initilized ContextFreeMapper
     * object used for mapping genotype to phenotype inside GELogger class.
     */
    GELogger(const string &path, unique_ptr<ContextFreeMapper> logMapper);

    /**
     *	@brief Log progress of current evolution run.
     *	@param [in] population Reference to population object.
     */
    void logProgress(const Population &population);

    /**
     * @brief Log result of evolution run.
     * @param [in] population Reference to population object.
     */
    void logResult(const Population &population);

    /**
     * @brief Getter of debug flag.
     * @return Current value of debug flag.
     */
    bool getDebug(void) const;

    /**
     * @brief Setter of debug flag.
     * @param [in] val New value of debug flag.
     */
    void setDebug(bool val);

    /**
     * @brief Logger class destructor.
     */
    ~GELogger();

  private:
    /**
     * @brief Fstream variable for Logger output file.
     */
    ofstream out;

    /**
     * @brief Nlohmann::json object.
     */
    json j_out;

    /**
     * @brief Unique poiter to ContextFreeMapper used to generate phenotype.
     */
    unique_ptr<ContextFreeMapper> mapper;

    /**
     * @brief Debug flag.
     * @details This flag is used to enable mapping genotype to phenotype in
     * GELogger::logProgress function that results in longer execution time.
     */
    bool debug = false;

    /**
     * @brief Path to ouput file.
     */
    string outpath;
};