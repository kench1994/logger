#pragma once
#include "IPrinter.hpp"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
namespace log_helper
{
    class ConsolePrinter
        : public IPrinter
    {
        public: 
            ConsolePrinter() {}
			virtual ~ConsolePrinter()
			{
				//TODO:flush
			}

			virtual int Init(std::string& strErrInfo, LogConfiguration* pConfigure = nullptr) override
			{
				if(pConfigure) m_Configure = *pConfigure;
				//m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				return 0;
			}

			virtual void Output(std::shared_ptr<LogLine> spLogLine) override
            {
				if (m_Configure.enLogLevel > spLogLine->enLevel)
					return;

				bool bResumeColor = false;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

				switch (spLogLine->enLevel)
				{
				case LogLevel::WARN:
					SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY));
					bResumeColor = true;
					break;
				case LogLevel::CRITAL:
					SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_INTENSITY));
					bResumeColor = true;
					break;
				}

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
				auto nPos = spLogLine->strFile.find_last_of("\\");
				std::cout << utils::time_helper::Stamp2TimeString(spLogLine->ullTimeStamp) \
					<< " [" \
					<< log_helper::getLevelName(spLogLine->enLevel) \
					<< "] " \
					<< std::move(fmt.str()) \
					<< " {" \
					<< (std::string::npos == nPos ? spLogLine->strFile : spLogLine->strFile.substr(nPos + 1)) \
					<< ":" \
					<< spLogLine->uLine \
					<< "}\n";

				if (XLOG_WARN <= spLogLine->enLevel)
					std::flush(std::cout);

				if (!bResumeColor)
					return;
				SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
            }
		private:
			LogConfiguration m_Configure;

    };
} // namespace log_helper
