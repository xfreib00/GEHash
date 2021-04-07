/**
 * @file main.cpp
 * @author Adam Freiberg
 * @brief Main file for generating hash functions using grammatical evolution
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <getopt.h>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include "GEHash.h"

using namespace chrono;

static void display_help(void)
{
	std::cout << std::endl << "Usage: GEHash [OPTIONS] ... [-i] FILE\n" <<
		   "Read BNF grammar from FILE and generate hash "
		   "function based on that grammar.\n" <<
		   "Example: GEHash -i grammar.txt -p 200\n" <<
		   "OPTIONS:\n" <<
		   "\t -h, --help\t\t Display help.\n" <<
		   "\t -i  --input\t\t Input file containing grammar. If not specified FILE is used.\n" <<
		   "\t -o  --output\t\t Output file for GELogger. Defaults to \"ouput.json\".\n" <<
		   "\t -g, --generations\t Max number of generations. Defaults to 5.\n" <<
		   "\t -p, --population\t Number of individuals in population. Defaults to 60.\n" <<
		   "\t -m  --magic\t\t Constant used in HTable hash function. Defaults to 0.\n" <<
		   "\t -w  --wrap\t\t Maximum number of wrapping operations on genotype to generate phenotype. Defaluts to 3.\n" <<
		   "\t -d  --debug\t\t Use debugging mode in logger class, which prints additional information. Not used by default.\n\n" <<
		   "FILE must contain grammar in BNF form. Grammar "
		   "will be parsed and used for GE of hash function.\n\n";
}

static std::string load_grammar(const std::string& path){

	if (path.empty()){
		throw std::invalid_argument("Given path is empty.");
	}
	/* open file and read content */
	std::fstream f;
	std::stringstream strS;

	f.open(path);

	if (f.peek() == std::fstream::traits_type::eof()){
		throw std::invalid_argument("Given file is empty or does not exist.");
	}

	/* read buffer to stringstream and then to string */
	strS << f.rdbuf();
	std::string str = strS.str();

	f.close();

	return str;
}

static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}


int main(int argc, char **argv){

	/* set options for getopt_long */
	int c = 0;
	struct option longopts[] = {
		{"population",	required_argument, 	NULL, 'p'},
		{"generations",	required_argument, 	NULL, 'g'},
		{"magic", 	required_argument, 	NULL, 'm'},
		{"wrap",	required_argument, 	NULL, 'w'},
		{"input", 	required_argument, 	NULL, 'i'},
		{"output", 	required_argument, 	NULL, 'o'},
		{"debug", 	no_argument, 		NULL, 'd'},
		{"help", 	no_argument, 		NULL, 'h'}
	};

	/* set default values of args */
	unsigned long population = 60;
	unsigned long generations = 5;
	uint64_t magic = 0;
	uint64_t wrap = 3;
	std::string input;
	std::string output = "output.json";
	bool input_defined = false, debug = false;

	if (argc < 2){
		std::cerr << "Not enough arguments. Use -h or --help to display help." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	while((c = getopt_long(argc, argv, ":p:g:m:w:o:i:dh", longopts, NULL)) != -1){
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
				output = trim(output);
				break;
			case 'i':
				input = optarg;
				input = trim(input);
				input_defined = true;
				break;
			case 'd':
				debug = true;
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
		/* load data from input file to input string */
		input = load_grammar(input);

		/* configure run based on given and default parameters */
		GEHash hash(generations,population);
		hash.SetGrammar(input,wrap);
		hash.SetLogger(output,debug);
		hash.SetEvaluator(magic);

		/* Run evolution */
		hash.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}