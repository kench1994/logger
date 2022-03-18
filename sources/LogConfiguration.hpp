#pragma once
#include <string>
#include <limits>
#include "LogLevel.hpp"
#include "DefaultFormater.hpp"
namespace log_helper
{
    struct LogConfiguration
    {
            LogConfiguration()
				: uStackTraceDepth(0), bWithThread(false), enLogLevel(LogLevel::INFO), spFormater(std::make_shared<DefaultFormater>())
			{}
			LogLevel enLogLevel;
            unsigned int uStackTraceDepth;
			bool bWithLine;
			bool bWithFile;
            bool bWithThread;
            std::shared_ptr<IFormater> spFormater;
    };
}
