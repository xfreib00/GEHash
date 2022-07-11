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

#include <filesystem>
#include <fstream>
#include <gram/language/mapper/ContextFreeMapper.h>
#include <gram/population/Population.h>
#include <gram/util/logger/Logger.h>
#include <nlohmann/json.hpp>

namespace GEHash {

/**
 * @brief Logger class for GEHash grammatical evolution.
 *
 * @details Class implements logger for GEHash using gram::Logger API. This
 * logger is called by GEEvolution class to log information about each
 * generation.
 */
class GELogger : public gram::Logger {

  public:
    /**
     * @brief Default constructor of Logger class.
     */
    GELogger() = default;

    /**
     * @brief Parameterized constructor of Logger class.
     *
     * @param [in] path Reference to path to output file.
     * @param [in] logMapper Unique pointer to initialized ContextFreeMapper
     * object used for mapping genotype to phenotype inside GELogger class.
     */
    GELogger(const std::filesystem::path &path,
             std::unique_ptr<gram::ContextFreeMapper> logMapper);

    void logStart(const uint64_t &p, const uint64_t &g, const uint64_t &t_size,
                  const double &prob);

    /**
     *	@brief Log progress of current evolution run.
     *
     *	@param [in] population Reference to population object.
     */
    void logProgress(const gram::Population &population) final;

    /**
     * @brief Log result of evolution run.
     *
     * @param [in] population Reference to population object.
     */
    void logResult(const gram::Population &population) final;

    /**
     * @brief Get value of debug flag.
     *
     * @return bool Return value of debug flag.
     */
    bool getDebug(void) const noexcept;

    /**
     * @brief Set value of debug flag.
     *
     * @param [in] val New value of debug flag.
     */
    void setDebug(bool val);

    /**
     * @brief Get path to output file.
     *
     * @return fs::path Return path to output file.
     */
    std::filesystem::path getOutputPath(void) const noexcept;

    /**
     * @brief Write out information stored in GELogger class to given output
     * stream.
     *
     * @param os Output stream object.
     * @param obj GElogger class object to be written to output stream.
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &os, const GELogger &obj);

    /**
     * @brief Logger class destructor.
     */
    ~GELogger();

  private:
    /**
     * @brief Using json identifier instead of Nlohmann::json.
     */
    using json = nlohmann::json;

    /**
     * @brief Fstream variable for Logger output file.
     */
    std::ofstream out;

    /**
     * @brief Nlohmann::json object.
     */
    json j_out{};

    /**
     * @brief Unique pointer to ContextFreeMapper used to generate phenotype.
     */
    std::unique_ptr<gram::ContextFreeMapper> mapper;

    /**
     * @brief Debug flag.
     *
     * @details This flag is used to enable mapping genotype to phenotype in
     * GELogger::logProgress function that results in longer execution time.
     */
    bool debug = false;

    /**
     * @brief Path to output file.
     */
    std::filesystem::path outpath{};
};

} // namespace GEHash