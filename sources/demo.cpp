#include "Logger.hpp"
#include "FilePrinter.hpp"
#include "ConsolePrinter.hpp"
#include <iostream>
int main()
{
	
	//std::cout << utils::time_helper::Stamp2TimeString(utils::time_helper::timestamp_now()) << std::endl;
	{
		std::string strErrInfo;
		auto spConsolePrinter = std::make_shared<log_helper::ConsolePrinter>();
		log_helper::Logger::GetInstance().AppendPrinter(spConsolePrinter);
		auto spFilePrinter = std::make_shared<log_helper::FilePrinter>();
		if (0 == spFilePrinter->Init(strErrInfo))
			log_helper::Logger::GetInstance().AppendPrinter(spFilePrinter);

	}
    std::thread t([](){
        for (;;)
        {

			log_helper::Logger::GetInstance().Consume();

            
        }
    });
	LOG(XLOG_WARN, "%s + %s = %c", "1", "2", '3');
	LOG(XLOG_ERROR, "%s + %s = %c", "2", "2", '4');
	t.join();
    return 0;
}