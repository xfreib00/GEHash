/**
 * @file evolution.cpp
 * @author Adam Freiberg
 * @brief Source file for GEHash class methods
 */

#include "evolution.h"

GEHash::GEHash(unsigned long generation, unsigned long population, std::string &outpath)
{
	if (generation < 2  && population < 50){
		throw std::invalid_argument("Invalid value of parameter.");
	}
		p = population;
		g = generation;

	log = std::make_unique<GELogger>(outpath);
}

void GEHash::Run(void)
{
	//gram::Evolution::Evolution();
}


/*
using namespace std::chrono;

void hash_speed()
{

	auto start = high_resolution_clock::now();

	auto end = high_resolution_clock::now();

	auto duration = duration_cast<nanoseconds>(end - start); 

}*/
