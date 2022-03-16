#include "blockqueue.hpp"
#define __LOG(loger, level, fmt, ...)\
{\
}
/* Returns microseconds since epoch */
static uint64_t timestamp_now()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
//todo time-format 学习下boost time
static void format_timestamp(std::ostream & os, uint64_t timestamp)
{
// The next 3 lines do not work on MSVC!
// auto duration = std::chrono::microseconds(timestamp);
// std::chrono::high_resolution_clock::time_point time_point(duration);
// std::time_t time_t = std::chrono::high_resolution_clock::to_time_t(time_point);
    char miliseconds[7];
    sprintf(miliseconds, "%03llu", timestamp % 1000);
    std::time_t time_t = timestamp / 1000;
    tm* gmtime = std::localtime(&time_t);
    
    if(nullptr == gmtime)
    {
        os << '[' << miliseconds << ']';
    }
    else
    {
        char datetime[32];
        sprintf(datetime, "%d-%02d-%02d %02d:%02d:%02d", gmtime->tm_year+YEAR, gmtime->tm_mon+MONTH,
            gmtime->tm_mday, gmtime->tm_hour, gmtime->tm_min, gmtime->tm_sec);
        os << '['<< datetime<< "."<< miliseconds << ']';
    }
}
//我认为log level应该是每个printer单独设置?
namespace utils
{
    class logger
    {
        public:
            logger() {}
            ~logger() {}
        protected:
            
        private:
            BlockingQueue<std::string> m_Logqueue;
    };
}