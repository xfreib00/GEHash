/**
 * @file evaluator.h
 * @author Adam Freiberg
 * @brief Header file for GEDriver class
 */

#ifndef GEHASH_DRIVER
#define GEHASH_DRIVER

#include <gram/evaluation/Evaluator.h>
#include <gram/individual/Fitness.h>
#include <gram/individual/Phenotype.h>
#include <gram/language/mapper/ContextFreeMapper.h>
#include "hashTable.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <array>
#include <math.h>

using namespace gram;

/**
 * @brief Class implemeting evaluation mechanism for GEHash. 
 */
class GEDriver : public Evaluator {

public:
    /**
     * @brief Default constructor. 
     */
    GEDriver() = default;

    /**
     * @brief Constructor of GEDriver class.
     * @param [in] magic Magic number used in grammar.
     */
    GEDriver(unsigned long magic);

    /**
     * @brief Calculate fitness for given program.
     * @param [in] program Generated string containing program.
     * @return Return calculated fitness for given program.
     * @exception If there is duplicity in training data throw hashInsertError exception.
     */
    Fitness calculateFitness(std::string program);
    
    /**
     * @brief Evaluate given phenotype.
     * @param [in out] phenotype Reference to phenotype to be evaluated.
     * @return Return calculated fitness function. Otherwise set fitness to high number.
     * @exception No exceptions guarantee.
     */
    Fitness evaluate(const Phenotype& phenotype) noexcept override;

    /**
     * @brief Default destructor. 
     */
    ~GEDriver() = default;

private:

    /**
     * @brief Instance of HTable used for evaluation of generated phenotype. 
     */
    HTable<uint16_t,string> table;

};

#endif