/**
 * @file driver.cpp
 * @author Adam Freiberg
 * @brief Source file for Driver class methods
 */

#include "driver.h"

GEDriver::GEDriver() : table(numeric_limits<uint32_t>::max())
{
    table = HTable(numeric_limits<uint32_t>::max());
}

Fitness GEDriver::calculateFitness(std::string program)
{

}

Fitness GEDriver::evaluate(const Phenotype& phenotype) noexcept
{
    try
    {
        return calculateFitness(phenotype);
    }
    catch(...)
    {
        return 1000.0;
    }
    
}