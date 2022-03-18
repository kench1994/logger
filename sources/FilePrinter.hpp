#pragma once
#include "IPrinter.hpp"
#include "TimeHelper.hpp"
#include <fstream>
#include <sstream>
namespace log_helper
{
	struct FileLogConfiguration 
		: public LogConfiguration
	{
		std::string strLogFilePath = ".";
		std::string strLogFilePosfix = "XLOG";
		std::string strLogFileType = "log";
	};

	class FilePrinter
		: public IPrinter
	{
	public:
		FilePrinter() {}
		virtual ~FilePrinter() 
		{
			m_ofStream.close();
		}


		virtual int Init(std::string& strErrInfo, LogConfiguration* pConfigure = nullptr) override
		{
			if (pConfigure)
			{
				m_Configure = *static_cast<FileLogConfiguration*>(pConfigure);
			}
			roll();

			return 0;
		}

		//单消费者
		//外部保证线程安全
		virtual void Output(std::shared_ptr<LogLine> spLogLine)
		{
			if (m_ullNextRollTimeStamp <= spLogLine->ullTimeStamp)
				roll();
			
			m_ofStream << m_Configure.spFormater->flat(spLogLine);

			if (XLOG_WARN <= spLogLine->enLevel)
				m_ofStream.flush();
		}
	protected:

		void close()
		{

		}

		void roll()
		{
			if(m_ofStream.is_open())
			{
				m_ofStream.flush();
				m_ofStream.close();
			}
			//获取下一天时间撮用于跨日判断
			m_ullNextRollTimeStamp = utils::time_helper::timestamp_today() + utils::time_helper::DayMillseconds;
			//TODO: 日志文件模式
			boost::format fmtLogFile("%s_%s.%s");
			fmtLogFile % m_Configure.strLogFilePosfix.c_str() % utils::time_helper::GetDateTime() % m_Configure.strLogFileType.c_str();
			std::string strLogFilePath;
			strLogFilePath.append(m_Configure.strLogFilePath).append("\\").append(std::move(fmtLogFile.str()));
			m_ofStream.open(strLogFilePath.c_str(), std::ios::app);
		}
	private:
		uint64_t m_ullNextRollTimeStamp;
		std::ofstream m_ofStream;
		FileLogConfiguration m_Configure;
	};
}