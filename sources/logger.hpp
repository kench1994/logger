#pragma once
#include "ParamPacker.hpp"
#include "BlockQueue.hpp"
#include <string>

/* Returns microseconds since epoch */
inline uint64_t timestamp_now()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
// //todo time-format 学习下boost time
// static void format_timestamp(std::ostream & os, uint64_t timestamp)
// {
// // The next 3 lines do not work on MSVC!
// // auto duration = std::chrono::microseconds(timestamp);
// // std::chrono::high_resolution_clock::time_point time_point(duration);
// // std::time_t time_t = std::chrono::high_resolution_clock::to_time_t(time_point);
//     char miliseconds[7];
//     sprintf(miliseconds, "%03llu", timestamp % 1000);
//     std::time_t time_t = timestamp / 1000;
//     tm* gmtime = std::localtime(&time_t);
    
//     if(nullptr == gmtime)
//     {
//         os << '[' << miliseconds << ']';
//     }
//     else
//     {
//         char datetime[32];
//         sprintf(datetime, "%d-%02d-%02d %02d:%02d:%02d", gmtime->tm_year+YEAR, gmtime->tm_mon+MONTH,
//             gmtime->tm_mday, gmtime->tm_hour, gmtime->tm_min, gmtime->tm_sec);
//         os << '['<< datetime<< "."<< miliseconds << ']';
//     }
// }
//我认为log level应该是每个printer单独设置?
namespace log
{
    typedef struct tagLogLine {
        tagLogLine() = delete;
        tagLogLine(unsigned int level,\
            const char* pszFile,\
            unsigned int line,\
            const char* pszFunction, \
            const char* pszFmt,\
            utils::ParamPacker&& params)
            : uLevel(level), strFile(pszFile), uLine(line), strFunction(pszFunction),\
            strLogFmt(pszFmt ? pszFmt : ""), stParams(params), ullTimeStamp(std::move(timestamp_now))
        {}
        uint64_t ullTimeStamp;
        unsigned int uLevel;
        std::string strFile;
        unsigned int uLine;
        std::string strFunction;
        std::string strLogFmt;
        utils::ParamPacker stParams;
    }LogLine;

    class logger
    {
        private:
            utils::BlockingQueue<std::unique_ptr<LogLine>> m_Logqueue;

        protected:
            static logger& logger::instance()
            {
                static logger s_logger;
                return s_logger;
            }

        public:
            logger() {}
            ~logger() {}

            utils::BlockingQueue<std::unique_ptr<LogLine>>& logger_cache()
            {
                return instance().m_Logqueue;
            }
    };
}

#define LOG(level, fmt, ...) \
{ \
utils::ParamPacker packer; \
packer.pack(##__VA_ARGS__); \
auto spLogLine = std::make_unique<log::LogLine>(level, \
__FILE__, static_cast<unsigned int>(__LINE__), __FUNCTION__, fmt, std::move(packer)); \
log::logger::instance().loger_cache().emplace_back(std::move(spLogLine)); \
}