/// @file service.h
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Service class. Entry point

#ifndef DOUANE_SERVICE_H
#define DOUANE_SERVICE_H

#include <log4cxx/logger.h>

class Service
{
private:
    /// Logger
    log4cxx::LoggerPtr logger;

    /// If true, debug mode is enabled
    bool m_debug;

    /// If true, it mean that the application is started as a service (fork)
    bool m_service;

    NetlinkListener netlink_listener;

public:
    /// Constructor
    Service();

    /// Destructor
    virtual ~Service();

    /// Run the application
    int run();

    /// Stop the application
    int stop(const int sig);

    /// Set the service mode
    inline void setServiceMode(const bool service)
    {
        m_service = service;
    }

    // TODO: Maybe useless in the future
    inline bool getServiceMode()
    {
        return m_service;
    }
};

#endif
