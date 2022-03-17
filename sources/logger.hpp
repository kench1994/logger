#pragma once
#include "LogLine.hpp"
#include "IPrinter.hpp"
#include "BlockQueue.hpp"
#include <string>
#include <unordered_map>
#include <boost/format.hpp>


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
namespace log_helper
{
    class Logger
    {
        private:
            utils::BlockingQueue<std::shared_ptr<LogLine>> m_Logqueue;

            std::mutex m_mtxPrinters;
            std::unordered_map<unsigned int, std::shared_ptr<IPrinter>> m_mapPrinters;
        protected:



        public:
            Logger() {}
            ~Logger() {}
            
			static Logger& GetInstance()
			{
				static Logger s_logger;
				return s_logger;
			}

            static utils::BlockingQueue<std::shared_ptr<LogLine>>& logger_cache()
            {
                return GetInstance().m_Logqueue;
            }

			//todo:can I check derive relation
			template <typename T>
            void AppendPrinter(std::shared_ptr<T> spPrinter)
            {
                std::lock_guard<std::mutex> lck(m_mtxPrinters);
				m_mapPrinters[m_mapPrinters.size()] = std::move(std::static_pointer_cast<IPrinter>(spPrinter));
            }

            //我认为线程由外部给到?
            //所以这边只提供消费方法?
            void Consume()
            {
                auto spLogLine = std::move(logger_cache().wait_and_pop());
                assert(spLogLine);
                for(auto&& itPrinter : m_mapPrinters)
                    itPrinter.second->Output(spLogLine);
            }
    };
}
//LogLine选用shared_ptr 因为数据可能有发往多个printer的需求
//比如文件printer 控制台printer 网络printer
#define LOG(level, fmt, ...) \
{ \
utils::ParamPacker packer; \
packer.pack(##__VA_ARGS__); \
auto spLogLine = std::make_shared<log_helper::LogLine>(level, \
__FILE__, static_cast<unsigned int>(__LINE__), __FUNCTION__, fmt, std::move(packer)); \
log_helper::Logger::logger_cache().push(std::move(spLogLine)); \
}
