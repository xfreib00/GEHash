/**
 * @file GEEvolution.h
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Header file for GEEvolution class
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <functional>
#include <memory>

#include <gram/evaluation/driver/EvaluationDriver.h>
#include <gram/population/Population.h>
#include <gram/util/logger/Logger.h>

using namespace std;

/**
 * @brief Reimplemented gram::Evolution class.
 * @details This class is reimplementation of gram's Evolution class, because
 * its current implementation does not support another argument in terminating
 * condition.
 */
class GEEvolution {
  public:
    /**
     * @brief Constructor of evaluator class.
     * @param [in out] evaluationDriver Unique pointer to EvaluationDriver
     * object used to evaluate given population.
     * @param [in out] logger Unique pointer to Logger object used to log
     * evolution progress and result.
     */
    GEEvolution(unique_ptr<gram::EvaluationDriver> evaluationDriver,
                unique_ptr<gram::Logger> logger);

    /**
     * @brief Function for executing evolution on given population.
     * @param [in] population Created population to be evaluated.
     * @param [in] terminatingCondition Std::function returning bool value,
     * which specifies terminating condition.
     * @return Returns final population after terminating condition is met.
     */
    gram::Population
    run(gram::Population population,
        function<bool(gram::Population &)> terminatingCondition) const;

    /**
     * @brief Function for executing evolution on given population.
     * @param [in] population Created population to be evaluated.
     * @param [in] gen Parameter used mainly as maximum number of generations.
     * Can be used in different way in terminatingCondion function.
     * @param [in] terminatingCondition Std::function returning bool value,
     * which specifies terminating condition.
     * @return Returns final population after terminating condition is met.
     */
    gram::Population run(gram::Population population, unsigned long gen,
                         function<bool(gram::Population &, unsigned long)>
                             terminatingCondition) const;

  private:
    /**
     * @brief Unique pointer to EvaulationDriver object specified in class
     * constructor.
     */
    std::unique_ptr<gram::EvaluationDriver> evaluationDriver;

    /**
     * @brief Unique pointer to Logger object specified in class constructor.
     */
    std::unique_ptr<gram::Logger> logger;
};