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
	std::cout << "Usage: GEHash [OPTIONS] ... FILE" << std::endl <<
		   "Read BNF grammar from FILE and generate hash "
		   "function based on that grammar." << std::endl <<
		   "Example: GEHash -i grammar.txt -p 200" << std::endl <<
		   "OPTIONS:" << std::endl <<
		   "\t -h, --help\t\t display help" << std::endl <<
		   "\t -i  --input\t\t input file containing grammar, if not specified FILE is used" << std::endl <<
		   "\t -o  --output\t\t output file for GELogger, defaults to ouput.json" << std::endl <<
		   "\t -g, --generations\t max number of generations, defaults to 5" << std::endl <<
		   "\t -p, --population\t number of individuals in population, defaults to 60" << std::endl <<
		   "\t -m  --magic\t\t constant used in HTable hash function, defaults to 0"<< std::endl << std::endl <<
		   "FILE must contain grammar in BNF form. Grammar "
		   "will be parsed and used for GE of hash function." << std::endl;
}


int main(int argc, char **argv){

	/* set options for getopt_long */
	int c = 0;
	struct option longopts[] = {
		{"population", required_argument, NULL, 'p'},
		{"generations", required_argument, NULL, 'g'},
		{"magic", required_argument, NULL, 'm'},
		{"wrap",required_argument, NULL , 'w'},
		{"input", required_argument, NULL, 'i'},
		{"output", required_argument, NULL, 'o'},
		{"help", no_argument, NULL, 'h'}
	};

	/* set default values of args */
	unsigned long population = 60;
	unsigned long generations = 5;
	uint64_t magic = 0;
	uint64_t wrap = 3;
	std::string input;
	std::string output = "output.json";
	bool input_defined = false;

	if (argc < 2){
		std::cerr << "Not enough arguments. Use -h or --help to display help." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	while((c = getopt_long(argc, argv, ":p:g:m:w:o:i:h", longopts, NULL)) != -1){
		switch(c){
			case 'p':
				try {
					population = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
					std::exit(EXIT_FAILURE);
				}
				break;
			case 'g':
				try {
					generations = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
					std::exit(EXIT_FAILURE);
				}
				break;
			case 'm':
				try {
					magic = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
					std::exit(EXIT_FAILURE);
				}
				break;
			case 'w':
				try {
					wrap = std::stoul(optarg,nullptr,0);
				}
				catch (...) {
					std::cerr << "Invalid input, use --help option"
					" to display help." << std::endl;
					std::exit(EXIT_FAILURE);
				}
				break;
			case 'o':
				output = optarg;
				break;
			case 'i':
				input = optarg;
				input_defined = true;
				break;
			case 'h':
				display_help();
				std::exit(EXIT_SUCCESS);
			case ':':
				std::cout << "Missing argument's value from option: " << static_cast<char>(optopt) << std::endl;
				std::exit(EXIT_FAILURE);
				break;
			case '?':
			default:
				std::cerr << "Invalid argument. Use -h or --help"
				" to display help" << std::endl;
				std::exit(EXIT_FAILURE);
				break;
		}
	}

	/* check if input file was defined */
	if ((optind != argc)){
		/* dual input file definition */
		if (input_defined){
			std::cerr << "Multiple input file definitions. "
			"Use -h or --help to display help" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		/*use last argv as input file if -i is not specified */
		input = argv[optind];
	}
	else
	{
		/* check if FILE and -i are both not used */
		if (!input_defined){
			std::cerr << "Input file required. "
			"Use -h or --help to display help" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

	//Set up and run evolution
	try
	{
		GEHash hash(generations,population);
		hash.SetGrammar(input,wrap);
		hash.SetLogger(output);
		hash.SetEvaluator(0xDEADBEEF);
		hash.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}