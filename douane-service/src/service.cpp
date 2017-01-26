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

// Log4cxx includes
#include <log4cxx/logger.h>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/patternlayout.h>

#include "service.h"


Service::Service()
{
    /// TODO: Entry point
}

Service::~Service()
{
    /// Destructor
}

int Service::run()
{
    return EXIT_SUCCESS;
}
