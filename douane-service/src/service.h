/// @file Service.h
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Service class. Entry point

#ifndef DOUANE_SERVICE_H
#define DOUANE_SERVICE_H

class Service
{
private:
    /// If true, debug mode is enabled
    bool m_debug;

    /// If true, it mean that the application is started as a service (fork)
    bool m_service;

    /// Log file path (shouldn't be hardcoded ?)
    std::string m_logFilePath = "/var/log/douane.log";

public:
    /// Constructor
    Service();

    /// Destructor
    virtual ~Service();

    /// Run the service
    int run();
};

#endif
