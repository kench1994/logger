#include "Logger.hpp"
#include "FilePrinter.hpp"
#include "ConsolePrinter.hpp"
#include <iostream>
#include <boost/timer.hpp>
#include <boost/format.hpp>
int main()
{
	
	//TODO:console printer 类似性能效率低的printer不应该和其他printer混用
	//std::cout << utils::time_helper::Stamp2TimeString(utils::time_helper::timestamp_now()) << std::endl;
	{
		std::string strErrInfo;
		//auto spConsolePrinter = std::make_shared<log_helper::ConsolePrinter>();
		//log_helper::Logger::GetInstance().AppendPrinter(spConsolePrinter);
		auto spFilePrinter = std::make_shared<log_helper::FilePrinter>();
		if (0 == spFilePrinter->Init(strErrInfo))
			log_helper::Logger::GetInstance().AppendPrinter(spFilePrinter);

	}
    std::thread trd([](){
        for (;;)
        {

			log_helper::Logger::GetInstance().Consume();

            
        }
    });
	double t1, t2, t3;
	//空跑步耗时
	boost::timer t;
	for (int i = 0; i < 1e6; ++i)
		t1 = t.elapsed();
	t.restart();
	//延迟format
	for (int i = 0; i < 1e6; ++i)
		LOG(XLOG_INFO, "[%-14.3f%-14.3f]", 12345.12345, 12345.12345);
	t2 = t.elapsed();
	t.restart();
	//立即format
	for (int i = 0; i < 1e6; ++i)
	{
		boost::format fmt("[%-14.3f%-14.3f]");
		fmt % 12345.12345 % 12345.12345;
		fmt.str();
	}
	t3 = t.elapsed();

	LOG(XLOG_ERROR, "[空跑延迟:%-14.3f,延迟format延迟%-14.3f,立即format延迟%-14.3f]", t1, t2, t3);
	trd.join();
    return 0;
}