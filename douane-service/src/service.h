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
    bool debug;

    /// If true, it mean that the application is started as a service (fork)
    bool service;

public:
    /// Constructor
    Service();

    /// Destructor
    virtual ~Service();

    /// Run the service
    int run();
};

#endif
