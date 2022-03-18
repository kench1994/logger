#pragma once
#include "IFormater.hpp"
#include <boost/format.hpp>
namespace log_helper
{
    class DefaultFormater 
        : virtual public IFormater
    {
        public:
            DefaultFormater() {}
            ~DefaultFormater(){}

            std::string flat(std::shared_ptr<LogLine>spLogLine) override
            {
				boost::format fmt(spLogLine->strLogFmt);
				for (auto&& it : spLogLine->stParams.vParams)
				{
					if (it.type() == typeid(int)) {
						fmt % boost::any_cast<int>(it);
					}
					else if (it.type() == typeid(unsigned int)) {
						fmt % boost::any_cast<unsigned int>(it);
					}
					else if (it.type() == typeid(unsigned long long)) {
						fmt % boost::any_cast<unsigned long long>(it);
					}
					else if (it.type() == typeid(const char*)) {
						fmt % boost::any_cast<const char*>(it);
					}
					else if (it.type() == typeid(std::string)) {
						fmt % boost::any_cast<std::string>(it).c_str();
					}
					else if (it.type() == typeid(char)) {
						fmt % boost::any_cast<char>(it);
					}
				}
				size_t nPos = 0;
                boost::format fmtFlattenData("%s [%s] %s {%s:%d}\n");
                fmtFlattenData % utils::time_helper::Stamp2TimeString(spLogLine->ullTimeStamp).c_str()
                               % log_helper::getLevelName(spLogLine->enLevel).c_str()
                               % fmt.str().c_str()
                               % (std::string::npos == (nPos = spLogLine->strFile.find_last_of("\\")) ?\
                                 spLogLine->strFile.c_str() : spLogLine->strFile.substr(nPos + 1).c_str()) \
                               % spLogLine->uLine;
                return fmtFlattenData.str();
				return "";
            }
    };
} // namespace log_helper
