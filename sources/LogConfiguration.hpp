#pragma once
#include <string>
#include <limits>
namespace utils
{
    namespace logger
    {
        enum class LogLevel : unsigned int{
            VERBOSE = 2,
            DEBUG = 3,
            INFO = 4,
            WARN = 5,
            ERROR = 6,
            //* Log level for XLog#init, printing all logs.
            ALL = 0,//Integer.MIN_VALUE,
            //* Log level for XLog#init, printing no log.
            NONE = (std::numeric_limits<unsigned int>::max)() //Integer.MAX_VALUE
        };


        //能不能用constexpr 或者模板代替?
        static const std::string getLevelName(LogLevel level)
        {
            switch (level) 
            {
                case LogLevel::VERBOSE:
                    return "VERBOSE";
                case LogLevel::DEBUG:
                    return "DEBUG";
                case LogLevel::INFO:
                    return "INFO";
                case LogLevel::WARN:
                    return "WARN";
                case LogLevel::ERROR:
                    return "ERROR";
            }
            return "";
        }

//         // Stringify log level with width of 5.
// static const char *stringifyLogLevel(LogLevel level) {
//   const char *levelName[] = {"TRAC", "DEBU", "INFO", "WARN", "ERRO", "FATA"};
//   return levelName[level];
// }

        class LogConfiguration
        {
            public:
                LogConfiguration(){}
                ~LogConfiguration(){}
            private:
                unsigned int m_uLogLevel;
                unsigned int m_uStackTraceDepth;
                bool m_bWithThread;


        };
    }
}