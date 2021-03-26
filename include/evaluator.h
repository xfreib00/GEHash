/**
 * @file evaluator.h
 * @author Adam Freiberg
 * @brief Header file for GEEvaluator class
 */

#ifndef GEHASH_EVALUATOR
#define GEHASH_EVALUATOR

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
#include <vector>

using namespace gram;

/**
 * @brief Class implemeting evaluation mechanism for GEHash. 
 */
class GEEvaluator : public Evaluator {

public:
    /**
     * @brief Default constructor. 
     */
    GEEvaluator() = default;

    /**
     * @brief Constructor of GEEvaluator class.
     * @param [in] magic Magic number used in grammar.
     */
    GEEvaluator(unsigned long magic);

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
    ~GEEvaluator() = default;

private:

    /**
     * @brief Instance of HTable used for evaluation of generated phenotype. 
     */
    HTable<uint16_t,std::array<uint32_t,9>> table;

    /**
     * @brief Private function for spliting strings.
     * @details Because std::string has no standard function for splitting strings each project needs to implement its own version.
     * Function used in this project is from answer found at <a href="https://stackoverflow.com/a/37454181">StackOverflow</a>.
     * @param [in] str String to be parsed.
     * @param [in] delim Delimiter used for splitting given string.
     * @return Returns vector of strings.
     */
    std::vector<std::string> split(const std::string& str, const std::string& delim);

};

#endif