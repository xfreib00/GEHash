/**
 * @file logger.cpp
 * @author Adam Freiberg
 * @brief Source file for Logger class methods
 */

#include "logger.h"

GELogger::GELogger(const std::string& path, unique_ptr<ContextFreeMapper> logMapper)
{
    /* check if path is not empty */
    if (path.empty()){
        throw std::invalid_argument("Missing GElogger path");
    }

    /* try to open file at given path */
    try
    {
        mapper = move(logMapper);
        out.open(path);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void GELogger::logProgress(const Population& population)
{
    json j;
    /* log best individual in current generation */
    j["status"] = "progress";
    j["gen"] = population.generationNumber();
    j["fitness"] = population.individualWithLowestFitness().fitness();
    if (debug){
        j["phenotype"]["code"] = population.individualWithLowestFitness().serialize(*mapper);
    }
    j_out.push_back(j);
}

void GELogger::logResult(const Population& population)
{
    json j;

    /* log best individual in final generation */
    j["status"] = "result";
    j["gen"] = population.generationNumber();
    j["fitness"] = population.individualWithLowestFitness().fitness();
    j["phenotype"]["code"] = population.individualWithLowestFitness().serialize(*mapper);

    j_out.push_back(j);

    /* write logger output to file */
    out << setw(4) << j_out << endl;
}

bool GELogger::getDebug(void)
{
    return debug;
}

void GELogger::setDebug(bool val)
{
    debug = val;
}

GELogger::~GELogger()
{
    /* close file */
    out.close();
}