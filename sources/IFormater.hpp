#pragma once
#include <memory>
#include "LogLine.hpp"
namespace log_helper
{
    class IFormater
    {
        public:
            IFormater() {}
            virtual ~IFormater() {};

            virtual std::string flat(std::shared_ptr<LogLine>) = 0;
    };
}