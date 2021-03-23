/**
 * @file evolution.cpp
 * @author Adam Freiberg
 * @brief Source file for GEHash class methods
 */

#include "evolution.h"

GEHash::GEHash(unsigned long generation, unsigned long population, std::string& outpath)
{
	if (generation < 2  || population < 50){
		throw std::invalid_argument("Invalid value of parameter.");
	}
		p = population;
		g = generation;

	//logging
	log = std::make_unique<GELogger>(outpath);

}

void GEHash::SetGrammar(std::string& grammar,unsigned long limit)
{
	if (grammar.empty()){
		throw std::invalid_argument("Grammar is empty string");
	}

	gramm = std::make_unique<ContextFreeGrammar>(parser.parse(grammar));
	cfm = std::make_unique<ContextFreeMapper>(std::move(gramm),limit);
}

void GEHash::SetEvaluator(unsigned long magic)
{
	eval = std::make_unique<GEDriver>(magic);
	cache = std::make_unique<EvaluatorCache>(move(eval));
	driver = std::make_unique<SingleThreadDriver>(move(cfm),move(cache));

}

void GEHash::Run(void)
{
	//selection
	unsigned long size = 5;
	auto numGen1 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	auto comparer = std::make_unique <LowFitnessComparer>();
	auto selector = std::make_unique <TournamentSelector>(size, move(numGen1), move(comparer));

	//crossover
	auto num2 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	auto crossover = std::make_unique<OnePointCrossover>(move(num2));

	//mutation
	Probability prob(0.1);
	auto numGen3 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	auto stepGen = std::make_unique<BernoulliStepGenerator>(prob, move(numGen3));
	auto numGen4 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	auto mutation = std::make_unique<CodonMutation>(move(stepGen), move(numGen4));

	//reproducer
	auto repr = std::make_unique<PassionateReproducer>(move(selector), move(crossover), move(mutation));

	auto num5 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	unsigned long len = 100;
	RandomInitializer in(move(num5),len);
	Population initial = in.initialize(p,move(repr));
	Evolution evol(move(driver),move(log));

	Population last_gen = evol.run(move(initial),[](Population& current_population)->bool{
		return current_population.lowestFitness() == 0.0;
	});
}