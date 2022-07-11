/**
 * @file GELogger.cpp
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Source file for GELogger class methods
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "GELogger.h"
#include "error/loggerError.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace GEHash {

/**
 * @brief Using fs identifier instead of std::filesystem to shorten code.
 */
namespace fs = std::filesystem;

GELogger::GELogger(const fs::path &path,
                   std::unique_ptr<gram::ContextFreeMapper> logMapper)
    : mapper{std::move(logMapper)}, outpath{path} {

    /* check if path exists */
    if (fs::exists(outpath)) {
        throw GEHashError::loggerInputError();
    }
}

void GELogger::logStart(const uint64_t &p, const uint64_t &g,
                        const uint64_t &t_size, const double &prob) {
    json j{};

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    j["header"] = {{"population", p},
                   {"generations", g},
                   {"tournament size", t_size},
                   {"mutation probability", prob}};

    std::stringstream s;
    s << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");

    j["start time"] = s.str();

    j_out.push_back(j);
}

void GELogger::logProgress(const gram::Population &population) {
    /* Temporary object used for storing data about current population.
       Log best individual in current generation. */
    json j = {{"status", "progress"},
              {"gen", population.generationNumber()},
              {"fitness", population.individualWithLowestFitness().fitness()}};

    /* if debug option is on, map and store phenotype of individual with
     * currently best fitness */
    if (debug) {
        try {
            j["phenotype"]["code"] =
                population.individualWithLowestFitness().serialize(*mapper);
        } catch (std::exception &e) {
            j["phenotype"]["code"] = e.what();
        }
    }
    /* store temporary object into output JSON object */
    j_out.push_back(j);
}

void GELogger::logResult(const gram::Population &population) {

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    /* Temporary object used for storing data about current population.
       Log best individual in final generation. */
    json j{{"status", "result"},
           {"gen", population.generationNumber()},
           {"fitness", population.individualWithLowestFitness().fitness()}};

    try {
        j["phenotype"]["code"] =
            population.individualWithLowestFitness().serialize(*mapper);
    } catch (const std::exception &e) {
        j["phenotype"]["code"] = e.what();
    }

    std::stringstream s;
    s << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");

    j["end time"] = s.str();

    /* store temporary object into output JSON object */
    j_out.push_back(j);

    try {
        out.open(outpath, std::ios::out);
        if (!out) {
            throw GEHashError::loggerOpenError();
        }
        /* write logger output to JSON file */
        out << j_out.dump(4) << std::endl;
        out.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

bool GELogger::getDebug(void) const noexcept { return debug; }

fs::path GELogger::getOutputPath(void) const noexcept { return outpath; }

void GELogger::setDebug(bool val) { debug = val; }

GELogger::~GELogger() {

    /* check if file is open */
    if (out.is_open()) {

        /* close file */
        out.close();
    }
}

std::ostream &operator<<(std::ostream &os, const GELogger &obj) {
    os << obj.j_out;
    return os;
}

} // namespace GEHash