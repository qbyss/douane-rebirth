/// @file log.cpp
/// @author qbyss
/// @date 27/01/2017
///
/// @brief Log implementation
///

#include <iostream>

// Log4cxx includes
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/patternlayout.h>

#include "log.h"

// Initialize the logger for the current file
log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("Log");

Log::Log()
{
	#ifdef DEBUG
	m_debug = true; // forced debug
	#else
	m_debug = false;
	#endif
}

Log::~Log()
{
	delete m_fileAppender;
}

void Log::init()
{
	std::cout << "Initializing logger" << m_debug << " " << m_logFilePath << std::endl;
	log4cxx::PatternLayoutPtr pattern = new log4cxx::PatternLayout(
	  this->m_debug ? "%d{dd/MM/yyyy HH:mm:ss} | %5p | [%F::%c:%L]: %m%n" : "%d{dd/MM/yyyy HH:mm:ss} %5p: %m%n"
	);

	m_fileAppender = new log4cxx::FileAppender(
	  log4cxx::LayoutPtr(pattern),
	  m_logFilePath
	);

	log4cxx::helpers::Pool pool;
	m_fileAppender->activateOptions(pool);
	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(m_fileAppender));
	log4cxx::Logger::getRootLogger()->setLevel(this->m_debug ? log4cxx::Level::getDebug() : log4cxx::Level::getInfo());

}
