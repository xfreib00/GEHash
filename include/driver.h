/**
 * @file driver.h
 * @author Adam Freiberg
 * @brief Header file for Driver class
 */

#ifndef GEHASH_DRIVER
#define GEHASH_DRIVER

#include <gram/evaluation/Evaluator.h>
#include <gram/individual/Fitness.h>
#include <gram/individual/Phenotype.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include "hashTable.h"
#include <limits>

using namespace gram;

class GEDriver : public Evaluator {

public:
    /**
     * @brief Constructor of GEDriver class. 
     */
    GEDriver();

    /**
     * @brief Calculate fitness for given program.
     * @param [in] program Generated string containing program.
     * @return Return calculated fitness for given program.
     */
    Fitness calculateFitness(std::string program);
    
    /**
     * @brief Evaluate given phenotype.
     * @param [in out] phenotype Reference to phenotype to be evaluated.
     * @return Return calculated fitness function. Otherwise set fitness to high number.
     */
    Fitness evaluate(const Phenotype& phenotype) noexcept override;

    ~GEDriver() = default;
private:
    HTable table;
};

#endif