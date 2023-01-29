/**
 * @file main.cpp
 * @author Adam Freiberg (xfreib00@stud.fit.vutbr.cz)
 * @brief Main file for generating hash functions using grammatical evolution
 * @version 0.1
 * @date 2021-07-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "GEHash.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * @brief Shorten namespace needed for working with std::filesystem header to
 * fs.
 */
namespace fs = std::filesystem;

/**
 * @brief Program's help message
 */
static constexpr const char *const help_string =
    "\n"
    "Usage: GEHash [OPTIONS] ... [-i] FILE\n"
    "Read BNF grammar from FILE and generate hash "
    "function based on that grammar.\n"
    "Example: GEHash -i grammar.txt -p 200\n"
    "OPTIONS:\n"
    "\t -h, --help\t\t Display help.\n"
    "\t -i  --input\t\t Input file containing grammar. If not specified "
    "FILE is used.\n"
    "\t -o  --output\t\t Output file for GELogger. Defaults to "
    "\"output.json\".\n"
    "\t -s  --set\t\t Training data file\\path. Defaults to "
    "\"data/train_set/train_set.data\".\n"
    "\t -g, --generations\t Max number of generations. Defaults to "
    "100.\n"
    "\t -p, --population\t Number of individuals in population. "
    "Defaults to 50.\n"
    "\t -m  --magic\t\t Constant used in HTable hash function. Defaults "
    "to 0.\n"
    "\t -w  --wrap\t\t Maximum number of wrapping operations on "
    "genotype to generate phenotype. Defaults to 3.\n"
    "\t -t  --tournament\t Number of individuals in tournament. "
    "Defaults to 5.\n"
    "\t -a  --probability\t Mutation probability between 0 and 1. "
    "Defaults to 0.1.\n"
    "\t -f  --fitWithSum\t Use fitness with sum. Defaults to false.\n"
    "\t -d  --debug\t\t Use debugging mode in logger class, which "
    "prints additional information. Not used by default.\n\n"
    "FILE must contain grammar in BNF form. Grammar "
    "will be parsed and used for GE of hash function.\n\n";

/**
 * @brief Read grammar from given file.
 *
 * @param [in] path Path to file containing grammar
 * @return std::string Contents read from file
 */
static std::string load_grammar(const fs::path &path) {

    if (!fs::exists(path)) {
        throw std::invalid_argument("File does not exist.");
    }

    /* open file */
    std::fstream f{};
    f.open(path);

    if (fs::is_empty(path)) {
        throw std::invalid_argument("Given file is empty.");
    }

    /* create stringstream to be read to */
    std::stringstream strS{};

    /* read buffer to stringstream and then to string */
    strS << f.rdbuf();
    std::string str = strS.str();

    f.close();

    return str;
}

/**
 * @brief Trim left side of string
 *
 * @param [in] str String to be trimmed
 * @param [in] chars Characters to be trimmed
 * @return std::string& Reference to resulting string
 */
static std::string ltrim(std::string str,
                         const std::string &chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

/**
 * @brief Trim right side of string
 *
 * @param [in] str String to be trimmed
 * @param [in] chars Characters to be trimmed
 * @return std::string& Reference to resulting string
 */
static std::string rtrim(std::string str,
                         const std::string &chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

/**
 * @brief Trim both sides of string
 * @details Function uses functions rtrim and ltrim. At first right side is
 * trimmed, then left.
 *
 * @param [in] str String to be trimmed
 * @param [in] chars Characters to be trimmed
 * @return std::string& Reference to resulting string
 */
static std::string trim(const std::string &str,
                        const std::string &chars = "\t\n\v\f\r ") {
    return ltrim(rtrim(str, chars), chars);
}

int main(int argc, char **argv) {

    /* Do not sync with C streams */
    std::ios::sync_with_stdio(false);

    /* set options for getopt_long */
    int c = 0;
    struct option longopts[] = {
        {"population", required_argument, nullptr, 'p'},
        {"generations", required_argument, nullptr, 'g'},
        {"magic", required_argument, nullptr, 'm'},
        {"wrap", required_argument, nullptr, 'w'},
        {"input", required_argument, nullptr, 'i'},
        {"output", required_argument, nullptr, 'o'},
        {"tournament", required_argument, nullptr, 't'},
        {"probability", required_argument, nullptr, 'a'},
        {"debug", no_argument, nullptr, 'd'},
        {"training", no_argument, nullptr, 's'},
        {"fitWithSum", no_argument, nullptr, 'f'},
        {"help", no_argument, nullptr, 'h'}};

    /* set default values of args */
    uint64_t population = 50;
    uint64_t generations = 100;
    uint64_t magic = 0;
    uint64_t wrap = 3;
    uint64_t t_size = 5;
    std::string input{};
    std::string output{"output.json"};
    std::string train_data{"data/train_set/train_set.data"};
    bool input_defined = false;
    bool debug = false;
    double prob = 0.1;
    bool useSum = false;

    if (argc < 2) {
        std::cerr << "Not enough arguments. Use -h or --help to display help."
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while ((c = getopt_long(argc, argv, ":p:g:m:w:o:i:t:s:a:dfh", longopts,
                            nullptr)) != -1) {
        switch (c) {
        case 'p':
            try {
                population = std::stoul(optarg, nullptr, 0);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }
            break;
        case 'g':
            try {
                generations = std::stoul(optarg, nullptr, 0);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }
            break;
        case 'm':
            try {
                magic = std::stoul(optarg, nullptr, 0);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }
            break;
        case 'w':
            try {
                wrap = std::stoul(optarg, nullptr, 0);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }
            break;
        case 't':
            try {
                t_size = std::stoul(optarg, nullptr, 0);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
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
        case 's':
            train_data = optarg;
            train_data = trim(train_data);
            break;
        case 'a':
            try {
                prob = std::stod(optarg, nullptr);
            } catch (...) {
                std::cerr << "Invalid input, use --help option"
                             " to display help."
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            debug = true;
            break;
        case 'f':
            useSum = true;
            break;
        case 'h':
            std::cout << help_string;
            std::exit(EXIT_SUCCESS);
        case ':':
            std::cout << "Missing argument's value from option: "
                      << static_cast<char>(optopt) << std::endl;
            std::exit(EXIT_FAILURE);
            break;
        case '?':
        default:
            std::cerr << "Invalid argument. Use -h or --help"
                         " to display help"
                      << std::endl;
            std::exit(EXIT_FAILURE);
            break;
        }
    }

    /* check if input file was defined */
    if ((optind != argc)) {
        /* dual input file definition */
        if (input_defined) {
            std::cerr << "Multiple input file definitions. "
                         "Use -h or --help to display help"
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
        /*use last argv as input file if -i is not specified */
        input = argv[optind];
    } else {
        /* check if FILE and -i are both not used */
        if (!input_defined) {
            std::cerr << "Input file required. "
                         "Use -h or --help to display help"
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    // Set up and run evolution
    try {
        /* load data from input file to input string */
        std::string grammar = load_grammar(fs::path(input));

        /* configure run based on given and default parameters */
        GEHash::GEHash hash(generations, population);
        hash.SetGrammar(grammar, wrap);
        hash.SetLogger(fs::path(output), debug);
        hash.SetEvaluator(magic, fs::path(train_data), useSum);
        hash.SetTournament(t_size);
        hash.SetProbability(prob);

        /* Run evolution */
        hash.Run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}