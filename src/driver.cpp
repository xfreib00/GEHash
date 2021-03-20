/**
 * @file driver.cpp
 * @author Adam Freiberg
 * @brief Source file for Driver class methods
 */

#include "driver.h"

GEDriver::GEDriver()
{
    table = HTable<uint16_t>();
}

Fitness GEDriver::calculateFitness(std::string program)
{
    return program.length();
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