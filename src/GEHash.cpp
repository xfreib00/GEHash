/**
 * @file GEHash.cpp
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Source file for GEHash class methods
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "GEHash.h"
#include "error/geError.h"
#include <functional>
#include <random>
#include <stdexcept>

namespace GEHash {

GEHash::GEHash(uint64_t generation, uint64_t population)
    : m_p{population}, m_g{generation} {
    if (generation < 2) {
        throw GEHashError::geGenerationError();
    }
    if (population < 10) {
        throw GEHashError::gePopulationError();
    }
}

void GEHash::SetLogger(const std::string &outpath, bool debug) {
    log = std::make_unique<GELogger>(outpath, std::move(cfmLogger));
    log->logStart(m_p, m_g, m_t_size, m_prob);
    if (debug) {
        log->setDebug(debug);
    }
}

void GEHash::SetGrammar(std::string &grammar, uint64_t limit) {
    if (grammar.empty()) {
        throw GEHashError::geGrammarError();
    }

    gramm = std::make_unique<gram::ContextFreeGrammar>(parser.parse(grammar));
    auto gramLogger =
        std::make_unique<gram::ContextFreeGrammar>(parser.parse(grammar));
    cfm = std::make_unique<gram::ContextFreeMapper>(std::move(gramm), limit);
    cfmLogger =
        std::make_unique<gram::ContextFreeMapper>(std::move(gramLogger), limit);
}

void GEHash::SetEvaluator(uint64_t magic, const std::string &data_path,
                          const bool &useSum) {
    eval = std::make_unique<GEEvaluator>(magic, data_path, useSum);
    cache = std::make_unique<gram::EvaluatorCache>(std::move(eval));
    driver = std::make_unique<gram::SingleThreadDriver>(std::move(cfm),
                                                        std::move(cache), true);
}

void GEHash::SetTournament(uint64_t size) {
    if (size < 2) {
        throw GEHashError::geTournamentError();
    }
    m_t_size = size;
}

void GEHash::SetProbability(double probability) {
    if (probability < 0.0 || probability > 1.0) {
        throw GEHashError::geMutationError();
    }
    m_prob = probability;
}

constexpr uint64_t GEHash::GetTournament(void) const { return m_t_size; }

constexpr double GEHash::GetProbability(void) const { return m_prob; }

constexpr uint64_t GEHash::GetPopulation(void) const { return m_p; }

constexpr uint64_t GEHash::GetGenerations(void) const { return m_g; }

void GEHash::Run(void) {
    // selection
    auto numGen1 = std::make_unique<gram::StdNumberGenerator<std::mt19937>>();
    auto comparer = std::make_unique<gram::LowFitnessComparer>();
    auto selector = std::make_unique<gram::TournamentSelector>(
        m_t_size, std::move(numGen1), std::move(comparer));

    // crossover
    auto num2 = std::make_unique<gram::StdNumberGenerator<std::mt19937>>();
    auto crossover = std::make_unique<gram::OnePointCrossover>(std::move(num2));

    // mutation
    gram::Probability prob(m_prob);
    auto numGen3 = std::make_unique<gram::StdNumberGenerator<std::mt19937>>();
    auto stepGen = std::make_unique<gram::BernoulliStepGenerator>(
        prob, std::move(numGen3));
    auto numGen4 = std::make_unique<gram::StdNumberGenerator<std::mt19937>>();
    auto mutation = std::make_unique<gram::CodonMutation>(std::move(stepGen),
                                                          std::move(numGen4));

    // reproducer
    auto repr = std::make_unique<gram::PassionateReproducer>(
        std::move(selector), std::move(crossover), std::move(mutation));

    auto num5 = std::make_unique<gram::StdNumberGenerator<std::mt19937>>();
    unsigned long len = 100;
    gram::RandomInitializer in(std::move(num5), len);
    gram::Population initial = in.initialize(m_p, std::move(repr));
    gram::Evolution evol(std::move(driver), std::move(log));

    gram::Population last_gen =
        evol.run(std::move(initial),
                 [&g = m_g](gram::Population &current_population) -> bool {
                     return current_population.lowestFitness() == 0.0 ||
                            current_population.generationNumber() == g;
                 });
}

} // namespace GEHash