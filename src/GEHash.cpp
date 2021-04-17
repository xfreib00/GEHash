/**
 * @file GEHash.cpp
 * @author Adam Freiberg
 * @brief Source file for GEHash class methods
 */

#include "GEHash.h"

GEHash::GEHash(unsigned long generation, unsigned long population)
{
	if (generation < 2  || population < 50){
		throw std::invalid_argument("Invalid value of parameter.");
	}
		p = population;
		g = generation;

}

void GEHash::SetLogger(const std::string& outpath, bool debug)
{
	log = std::make_unique<GELogger>(outpath,move(cfmLogger));
	if (debug){
		log->setDebug(debug);
	}
}

void GEHash::SetGrammar(std::string& grammar,unsigned long limit)
{
	if (grammar.empty()){
		throw std::invalid_argument("Grammar is empty string");
	}

	gramm = std::make_unique<ContextFreeGrammar>(parser.parse(grammar));
	auto gramLogger = std::make_unique<ContextFreeGrammar>(parser.parse(grammar));
	cfm = std::make_unique<ContextFreeMapper>(std::move(gramm),limit);
	cfmLogger = std::make_unique<ContextFreeMapper>(std::move(gramLogger),limit);
}

void GEHash::SetEvaluator(unsigned long magic, const std::string& data_path)
{
	eval = std::make_unique<GEEvaluator>(magic, data_path);
	cache = std::make_unique<EvaluatorCache>(move(eval));
	driver = std::make_unique<SingleThreadDriver>(move(cfm),move(cache),true);

}

void GEHash::SetTournament(unsigned long size)
{
	t_size = size;
}

void GEHash::Run(void)
{
	//selection
	auto numGen1 = std::make_unique<StdNumberGenerator<std::mt19937>>();
	auto comparer = std::make_unique <LowFitnessComparer>();
	auto selector = std::make_unique <TournamentSelector>(t_size, move(numGen1), move(comparer));

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
	GEEvolution evol(move(driver),move(log));

	Population last_gen = evol.run(move(initial),g,[](Population& current_population,unsigned long gen)->bool{
		return current_population.lowestFitness() == 0.0 || current_population.generationNumber() == gen;
	});
}