/**
 * @file main.cpp
 * @author Adam Freiberg
 * @brief Main file for generating hash functions using grammatical evolution
 */

#include <iostream>
#include <functional>
#include <getopt.h>
#include <string>
#include <cstdlib>
#include "GEHash.h"

static void display_help(void)
{
	std::cout << "Usage: GEHash [OPTIONS]... FILE" << std::endl <<
		   "Read BNF grammar from FILE and generate hash "
		   "function based on that grammar." << std::endl <<
		   "Example: GEHash -i grammar.txt -p 200" << std::endl <<
		   "OPTIONS:" << std::endl <<
		   "\t -h, --help\t\t display help" << std::endl <<
		   "\t -g, --generations\t max number of generations" << std::endl <<
		   "\t -p, --population\t number of individuals "
		   "in population" << std::endl << std::endl <<
		   "FILE must contain grammar in BNF form. Grammar "
		   "will be parsed and used for GE of hash function." << std::endl;
}


int main(int argc, char **argv){

	/* set options for getopt_long */
	int c = 0;
	struct option longopts[] = {
		{"population", optional_argument, NULL, 'p'},
		{"generations", optional_argument, NULL, 'g'},
		{"output", required_argument, NULL, 'o'},
		{"help", no_argument, NULL, 'h'}
	};	
	unsigned long population = 60;
	unsigned long generations = 5;
	std::string output;

	if (argc < 2){
		std::cout << "FAILURE" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string bnf_grammar("");

	while((c = getopt_long(argc, argv, ":p:g:o:h", longopts, NULL)) != -1){
		switch(c){
			case 'p':
				try {
					population = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
				}
				break;
			case 'g':
				try {
					generations = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
				}
				break;
			case 'o':
				output = optarg;
				break;
			case 'h':
				display_help();
				break;
			case ':':
				std::cout << "Something is missing: " << optarg << ", " << optind << std::endl;	
				break;
			case '?':
				std::cerr << "Invalid argument. Use --help"
				" to display help" << std::endl;
				break;
		}
	}

	//Create and run evolution
	try
	{
		//std::cout << "Got thru params: " << output << std::endl;
		GEHash hash(generations,population);
		hash.SetGrammar(bnf_grammar,3);
		hash.SetLogger(output);
		hash.SetEvaluator(0xDEADBEEF);
		hash.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
