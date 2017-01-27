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

#include "netlink_listener.h"
#include "freedesktop/desktop_files.h"
#include "rules_manager.h"
#include "processes_manager.h"
#include "dbus/dbus_server.h"
#include "service.h"
#include "log.h"

   // TODO: Better in dynamic ?


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

    /*
    ** ~~~~ Global class initializations ~~~~
    */

    DesktopFiles          desktop_files;
    RulesManager          rules_manager;
    ProcessesManager      processes_manager;
    DBusServer            dbus_server;

    try
    {
        processes_manager.set_desktop_files(&desktop_files);
        netlink_listener.set_processes_manager(&processes_manager);
        dbus_server.set_rules_manager(&rules_manager);

        /*
        ** ~~~~ Signal connexions ~~~~
        */

        LOG4CXX_DEBUG(logger, "Connecting objects");
        // When NetlinkListener emit connected_to_kernel_module signal then fire RulesManager::push_rules
        netlink_listener.on_connected_to_kernel_module_connect(boost::bind(&RulesManager::push_rules, &rules_manager));

        // When NetlinkMessageHandler emit new_network_activity signal then fire RulesManager::lookup_activity
        NetlinkMessageHandler::on_new_network_activity_connect(boost::bind(&RulesManager::lookup_activity, &rules_manager, _1));

        // When RulesManager emit new_unknown_activity signal then fire the DBusServer signal NewActivityToBeValidated
        rules_manager.on_new_unknown_activity_connect(boost::bind(&DBusServer::signal_new_unknown_activity, &dbus_server, _1));

        // When D-Bus Douane emit new_rule_received signal then fire RulesManager::make_rule_from
        Douane::on_new_rule_received_connect(boost::bind(&RulesManager::make_rule_from, &rules_manager, _1, _2));

        // When RulesManager emit new_network_activity signal then fire NetlinkListener::send_rule
        rules_manager.on_new_rule_created_connect(boost::bind(&NetlinkListener::send_rule, &netlink_listener, _1));

        // When RulesManager emit rule_deleted signal then fire NetlinkListener::delete_rule
        rules_manager.on_rule_deleted_connect(boost::bind(&NetlinkListener::delete_rule, &netlink_listener, _1));
        //
        // TODO: Emit a signal to the external process which will popup a dialog to ignore the activity
        //rules_manager.on_rule_deleted_connect(boost::bind(&GtkQuestionWindow::forget_unknown_application, &douane_external_dialog, _1));

        // Listener send all received activity to the D-Bus server so that it can fire a signal
        NetlinkMessageHandler::on_new_network_activity_connect(boost::bind(&DBusServer::new_network_activity, &dbus_server, _1));
        /*
        **/

        /*
        ** ~~~~ Service starting ~~~~
        */
        // D-Bus server runs in a thread
        dbus_server.start();

        /* Connect and listen to the Linux Kernel Module
        **
        *  The NetlinkListener is the core of the service.
        *  This means that the following start() method is the method which will runs until the daemon has to die.
        */
        netlink_listener.start();
    }
    catch(const std::exception &e)
    {
        LOG4CXX_ERROR(logger, e.what());
    }
    catch (const std::string &e)
    {
        LOG4CXX_ERROR(logger, e);
    }
    catch(...)
    {
        LOG4CXX_ERROR(logger, "Unknown error occured!");
    }

    return EXIT_SUCCESS;
}

int Service::stop(const int sig)
{
    LOG4CXX_INFO(logger, "Exiting Douane with signal " << sig << "...");
    netlink_listener.say_goodbye();

    return EXIT_SUCCESS;
}
