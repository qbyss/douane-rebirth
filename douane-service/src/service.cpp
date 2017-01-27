/// @file service.cpp
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Service implementation
///

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <boost/bind.hpp>
#include <signal.h>

#include "service.h"
#include "log.h"


Service::Service()
: logger(log4cxx::Logger::getLogger("Service"))
{
    /// TODO: Entry point

}

Service::~Service()
{
    /// Destructor
}

int Service::run()
{
    LOG4CXX_DEBUG(logger, "Service initialization...");
    return EXIT_SUCCESS;
}
