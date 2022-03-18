#pragma once
#include <limits>
#include <string>
namespace log_helper
{

    enum class LogLevel : unsigned int{
        VERBOSE = 2,
        DEBUG = 3,
        INFO = 4,
        WARN = 5,
        CRITAL = 6,
        //* Log level for XLog#init, printing all logs.
        ALL = 0,//Integer.MIN_VALUE,
        //* Log level for XLog#init, printing no log.
        NONE = (std::numeric_limits<unsigned int>::max)() //Integer.MAX_VALUE
    };


    //能不能用constexpr 或者模板代替?
    inline std::string getLevelName(LogLevel level)
    {
        switch (level) 
        {
            case LogLevel::VERBOSE:
                return "VERBO";
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO ";
            case LogLevel::WARN:
                return "WARN ";
            case LogLevel::CRITAL:
                return "ERROR";
        }
        return "    ";
    }

// Stringify log level with width of 5.
// static const char *stringifyLogLevel(LogLevel level) {
//   const char *levelName[] = {"TRAC", "DEBU", "INFO", "WARN", "ERRO", "FATA"};
//   return levelName[level];
// }
    
} // namespace log_helper

#define XLOG_VERBOSE log_helper::LogLevel::VERBOSE
#define XLOG_DEBUG log_helper::LogLevel::DEBUG
#define XLOG_INFO log_helper::LogLevel::INFO
#define XLOG_WARN log_helper::LogLevel::WARN
#define XLOG_ERROR log_helper::LogLevel::CRITAL
