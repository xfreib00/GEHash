/**
 * @file GEEvolution.cpp
 * @author Adam Freiberg
 * @brief Source file for GEEvolution class methods
 */

#include "GEEvolution.h"

GEEvolution::GEEvolution(unique_ptr<gram::EvaluationDriver> evaluationDriver, unique_ptr<gram::Logger> logger)
    : evaluationDriver(move(evaluationDriver)), logger(move(logger)) {
  //
}

gram::Population GEEvolution::run(gram::Population population, function<bool(gram::Population&)> terminatingCondition) const {
  evaluationDriver->evaluate(population.allIndividuals());

  while (!terminatingCondition(population)) {
    logger->logProgress(population);

    population.reproduce();

    evaluationDriver->evaluate(population.allIndividuals());
  }

  logger->logResult(population);

  return population;
}

gram::Population GEEvolution::run(gram::Population population, unsigned long gen, function<bool(gram::Population&, unsigned long)> terminatingCondition) const {
  evaluationDriver->evaluate(population.allIndividuals());

  while (!terminatingCondition(population,gen)) {
    logger->logProgress(population);

    population.reproduce();

    evaluationDriver->evaluate(population.allIndividuals());
  }

  logger->logResult(population);

  return population;
}