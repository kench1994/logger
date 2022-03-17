#pragma once
#include <boost/format.hpp>
#include "TimeHelper.hpp"
#include "ParamPacker.hpp"
#include "LogConfiguration.hpp"

namespace log_helper
{
        typedef struct tagLogLine {
        tagLogLine() = delete;
        tagLogLine(LogLevel level,\
            const char* pszFile,\
            unsigned int line,\
            const char* pszFunction, \
            const char* pszFmt,\
            utils::ParamPacker&& params)
            : enLevel(level), strFile(pszFile), uLine(line), strFunction(pszFunction),\
            strLogFmt(pszFmt ? pszFmt : ""), stParams(params), ullTimeStamp(std::move(utils::time_helper::timestamp_now()))
        {}
        uint64_t ullTimeStamp;
		LogLevel enLevel;
        std::string strFile;
        unsigned int uLine;
        std::string strFunction;
        std::string strLogFmt;
        utils::ParamPacker stParams;
    }LogLine;

}