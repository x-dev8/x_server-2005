#ifndef __LOG4CPP_LOGGER_H__
#define __LOG4CPP_LOGGER_H__

#include "logger_interface.h"

#include "Log4cpp\Category.hh"
#include "Log4cpp\PropertyConfigurator.hh"

#include <string>

#ifdef LOG_PRIORITY_FATAL
#undef LOG_PRIORITY_FATAL
#endif
#define LOG_PRIORITY_FATAL    Log4cppLogger::FATAL

#ifdef LOG_PRIORITY_ALERT
#undef LOG_PRIORITY_ALERT
#endif
#define LOG_PRIORITY_ALERT    Log4cppLogger::ALERT

#ifdef LOG_PRIORITY_CRITICAL
#undef LOG_PRIORITY_CRITICAL
#endif
#define LOG_PRIORITY_CRITICAL Log4cppLogger::CRITICAL

#ifdef LOG_PRIORITY_ERROR
#undef LOG_PRIORITY_ERROR
#endif
#define LOG_PRIORITY_ERROR    Log4cppLogger::ERR

#ifdef LOG_PRIORITY_WARNING
#undef LOG_PRIORITY_WARNING
#endif
#define LOG_PRIORITY_WARNING  Log4cppLogger::WARNING

#ifdef LOG_PRIORITY_NOTICE
#undef LOG_PRIORITY_NOTICE
#endif
#define LOG_PRIORITY_NOTICE   Log4cppLogger::NOTICE

#ifdef LOG_PRIORITY_INFO
#undef LOG_PRIORITY_INFO
#endif
#define LOG_PRIORITY_INFO     Log4cppLogger::INFO

#ifdef LOG_PRIORITY_DEBUG
#undef LOG_PRIORITY_DEBUG
#endif
#define LOG_PRIORITY_DEBUG    Log4cppLogger::DEBUG

#ifdef LOG_PRIORITY_NOTSET
#undef LOG_PRIORITY_NOTSET
#endif
#define LOG_PRIORITY_NOTSET   Log4cppLogger::NOTSET

#ifdef LOG_CONFIGURE
#undef LOG_CONFIGURE
#endif
#define LOG_CONFIGURE Log4cppLogger::Instance().Configure

#ifdef LOG_MESSAGE
#undef LOG_MESSAGE
#endif
#define LOG_MESSAGE Log4cppLogger::Instance().Print


/**
 * @brief log4cpp wrapper class.
 */
class Log4cppLogger : public LoggerInterface
{
// Type definition and constant.
public:
    enum PriorityLevel
    {
        EMERG    = 0,
        FATAL    = 0,
        ALERT    = 100,
        CRITICAL = 200,
        ERR		 = 300,
        WARNING  = 400,
        NOTICE   = 500,
        INFO     = 600,
        DEBUG    = 700,
        NOTSET   = 800
    };

// Construction.
private:
    /// Constructor.
    Log4cppLogger() {}

    /// Destructor.
    virtual ~Log4cppLogger() {}

// Overload operator.
private:
    /// Disable copy constructor.
    Log4cppLogger( const Log4cppLogger& object );

    /// Disable assignment operator.
    Log4cppLogger& operator =( const Log4cppLogger& object );

// Method.
public:
    /// Instantiation Log4cppLogger object.
    static Log4cppLogger& Instance()
    {
        static Log4cppLogger logger;
        return logger;
    }

// Override.
public:
    /// Load configure.
    virtual void Configure( const std::string& configFile ) throw( ConfigureException )
    {
        try
        { 
            log4cpp::PropertyConfigurator::configure( configFile );
        } 
        catch( log4cpp::ConfigureFailure& reason )
        {
            throw ConfigureException( reason.what()  );
        }
    }

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const char* format, ... ) throw()
    {
#ifdef _DEBUG

        va_list args;
        va_start( args, format );

        log4cpp::Category::getInstance( categoryName ).logva( priority, format, args );

        va_end( args );
#endif // _DEBUG
    };

    /// Log a message with the specified category and priority.
    virtual void Print( const std::string& categoryName, int priority, const std::string& message ) throw()
    {
#ifdef _DEBUG  //lyh屏蔽日志 2个Print

        log4cpp::Category::getInstance( categoryName ).log( priority, message );
#endif 
    };
};

#endif // __LOG4CPP_LOGGER_H__
