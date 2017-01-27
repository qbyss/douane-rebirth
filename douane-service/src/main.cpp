// Basic includes
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

// Douane internal includes
#include "netlink_listener.h"
#include "freedesktop/desktop_files.h"
#include "rules_manager.h"
#include "processes_manager.h"
#include "dbus/dbus_server.h"
#include "service.h"
#include "log.h"

// In the case the Makefile didn't initialized the VERSION variable
// this code initialize it to "UNKNOWN"
#ifndef DOUANE_VERSION
#define DOUANE_VERSION "UNKNOWN"
#endif

// Global initialization
// The service needs to be global because of the signal handler
Service *s=nullptr;

/// Handle exit signal
void handler(int sig)
{
    exit(s->stop(sig));
}


void do_service(void)
{
  // Create child process
  switch(fork())
  {
    case -1:
    {
      std::cerr << "Unable to create service process" << std::endl;
      exit(-1);
    }
    case 0:
    {
      //unmask the file mode
      umask(0);

      if(setsid() < 0)
      {
        std::cout << "ERROR: Unable to set new session" << std::endl;
        // Return failure
        exit(1);
      }
      break;
    }
    default:
    {
      // Parent process can quit
      exit(0);
    }
  }
}

int main(int argc, char * argv[])
{
    Log *l = new Log();
    Service *s = new Service();

    // CTRL + C catcher
    signal(SIGINT, handler);

    // Force the nice value to -20 (urgent)
    nice(-20);

    // Handle arguments
    int c;
    const struct option long_options[] =
    {
        {"service",    no_argument,       0, 's'},
        {"version",   no_argument,       0, 'v'},
        {"help",      no_argument,       0, 'h'},
        {"log-file",  required_argument, 0, 'l'},
        {"debug",     no_argument      , 0, 'D'},
        {0,0,0,0}
    };

    int option_index = 0;
    while ((c = getopt_long(argc, argv, "dvh:l:D", long_options, &option_index)) != -1)
    {
        switch (c)
        {
            case 's':
                // s->setServiceMode(true);
                break;
            case 'v':
                std::cout << "douane-rebirth version " << DOUANE_VERSION << std::endl;
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                std::cout << "Not help available at this moment" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            case 'l':
                l->setLogFile(optarg);
                break;
            case 'D':
                l->setDebug(true);
                break;
            case '?':
                std::cout << std::endl << "To get help execute me with --help" << std::endl;
                exit(1);
                break;
            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    try {
        // Initialize the logger
        l->init();

        // Fork the application if the service mod is enabled
        if (s->getServiceMode())
        {
          do_service();
        }

        return s->run();
  }
  catch(...)
  {
      std::cerr << "Unhandled exception" << std::endl;
  }
}
