#pragma once
#include "IFormater.hpp"
#include <boost/format.hpp>
#include <utils/unique_array.hpp>
#ifdef _DEBUG
#include <iostream>
#endif

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
				boost::format fmt(spLogLine->strLogFmt.c_str());
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
					else if(it.type() == typeid(float)){
						fmt % boost::any_cast<float>(it);
					}
					else if(it.type() == typeid(double)){
						fmt % boost::any_cast<double>(it);
					}
				}
				size_t nPos = 0;
				//TODO:string_view
				std::string strFileName = (std::string::npos == (nPos = spLogLine->strFile.find_last_of("\\")) ? spLogLine->strFile : spLogLine->strFile.substr(nPos + 1));
				//预估需要的空间
				size_t nReserveSize = fmt.str().length() + strFileName.length() + 42;
				utils::unique_array<char> auto_buffer(new char[nReserveSize]);
				memset(auto_buffer.get(), '\0', nReserveSize);
				sprintf_s(auto_buffer.get(), nReserveSize - 1, "%s [%s] %s {%s:%d}\n",\
					utils::time_helper::Stamp2TimeString(spLogLine->ullTimeStamp).c_str(), \
					log_helper::getLevelName(spLogLine->enLevel).c_str(), \
					fmt.str().c_str(), \
					strFileName.c_str(), \
					spLogLine->uLine
				);
				//TODO:how can i avoid string construct copy
				std::string ss(auto_buffer.get());
				return ss;
            }
    };
} // namespace log_helper
