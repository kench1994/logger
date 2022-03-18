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

				std::cout << m_Configure.spFormater->flat(spLogLine);

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
