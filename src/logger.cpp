/**
 * @file logger.cpp
 * @author Adam Freiberg
 * @brief Source file for Logger class methods
 */

#include "logger.h"

GELogger::GELogger(const std::string& path)
{
    if (path.empty()){
        throw std::invalid_argument("Missing Logger path");
    }
    out.open(path);
}

void GELogger::logProgress(const Population& population)
{
    
}

void GELogger::logResult(const Population& population)
{

}

GELogger::~GELogger()
{
    out.close();
}