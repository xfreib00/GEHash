/**
 * @file GELogger.cpp
 * @author Adam Freiberg
 * @brief Source file for GELogger class methods
 */

#include "GELogger.h"

GELogger::GELogger(const string& path, unique_ptr<ContextFreeMapper> logMapper)
{
    /* check if path is not empty */
    if (path.empty()){
        throw loggerInputError();
    }

    /* try to open file at given path */
    try
    {
        mapper = move(logMapper);
        out.open(path);
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

void GELogger::logProgress(const Population& population)
{
    /* temporary object used for storing data about current population */
    json j;

    /* log best individual in current generation */
    j["status"] = "progress";
    j["gen"] = population.generationNumber();
    j["fitness"] = population.individualWithLowestFitness().fitness();

    /* if debug option is on, map and store phenotype of individual with currently best fitness */
    if (debug){
        try
        {
            j["phenotype"]["code"] = population.individualWithLowestFitness().serialize(*mapper);
        }
        catch (std::exception& e)
        {
            j["phenotype"]["code"] = e.what();
        }
    }

    /* store temporary object into ouput JSON object */
    j_out.push_back(j);

}

void GELogger::logResult(const Population& population)
{
    /* temporary object used for storing data about current population */
    json j;

    /* log best individual in final generation */
    j["status"] = "result";
    j["gen"] = population.generationNumber();
    j["fitness"] = population.individualWithLowestFitness().fitness();
    try
    {
        j["phenotype"]["code"] = population.individualWithLowestFitness().serialize(*mapper);
    }
    catch(const std::exception& e)
    {
        j["phenotype"]["code"] = e.what();
    }

    /* store temporary object into ouput JSON object */
    j_out.push_back(j);

    /* write logger output to JSON file */
    out << setw(4) << j_out.dump() << endl;
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