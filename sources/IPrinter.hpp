#pragma once
#include "LogLine.hpp"
#include "LogConfiguration.hpp"

namespace log_helper
{
    class IPrinter
    {
        public:
            IPrinter() {}

			virtual ~IPrinter() {}
            
			virtual int Init(std::string&, LogConfiguration* = nullptr) = 0;

			virtual void Output(std::shared_ptr<LogLine>) = 0;
        private:

    };
} // namespace log_helper