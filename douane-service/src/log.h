/// @file log.h
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Log management class for log4cxx

#ifndef DOUNAE_LOG_H
#define DOUANE_LOG_H

class Log
{
private:
	/// If true, debug mode is on
	bool m_debug;

	/// Log file path (shouldn't be hardcoded ?)
	std::string m_logFilePath = "/var/log/douane.log";
public:
	/// Initialize log4cxx
	/// @param debug If true, log4cxx will be in debug mode
	Log(const bool debug);

	virtual ~Log();
};

#endif
