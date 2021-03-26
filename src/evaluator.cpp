/**
 * @file evaluator.cpp
 * @author Adam Freiberg
 * @brief Source file for GEDriver class methods
 */

#include "evaluator.h"

GEDriver::GEDriver(unsigned long magic)
{
    table.setMagic(magic);
}

Fitness GEDriver::calculateFitness(std::string program)
{
    Fitness fit = 0.0;
    /* set up table for */
    table.setFunc(program);

    std::array<uint16_t,numeric_limits<uint16_t>::max()> arr;

    /* open file containing train data */
    std::ifstream f("../data/train_set/train_set.data");

    /* insert training data to hash table */
    for (std::string line; getline(f,line);){
        try
        {
            table.Insert(line);
        }
        catch (hashInsertError &e)
        {
            throw;
        }
    }

    /* get counts at each index */
    arr = table.getDimensions();

    /* calculate fitness as weighted  */
    for (auto a : arr){
        if (a > 1){
            fit += pow(a,2);
        }
    }

    return fit;
}

Fitness GEDriver::evaluate(const Phenotype& phenotype) noexcept
{
    try
    {
        return calculateFitness(phenotype);
    }
    catch(hashInsertError &e)
    {
        std::cerr << "Duplicity in training data: " << e.what()
        << std::endl;
        return 2000.0;
    }
    catch(...)
    {
        return 1000.0;
    }
    
}