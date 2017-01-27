/// @file log.h
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Log management class for log4cxx

#ifndef DOUNAE_LOG_H
#define DOUANE_LOG_H

#include <log4cxx/logger.h>

class Log
{
private:
	/// If true, debug mode is on
	bool m_debug;

	/// Log file path (shouldn't be hardcoded ?)
	#ifdef DEBUG
	std::string m_logFilePath = "d.log"; // "/var/log/douane.log";
	#else
	std::string m_logFilePath = "/var/log/douane.log";
	#endif
public:
	/// Initialize log4cxx
	Log();

	virtual ~Log();

	/// Initialize log4cxx
	/// Delayed initialization because of the user input
	void init();

	/// Set debug mode
	inline void setDebug(const bool debug)
	{
		m_debug = debug;
	}

	/// Change the log file path
	inline void setLogFile(const std::string & logFilePath)
	{
		m_logFilePath = logFilePath;
	}
};

#endif
