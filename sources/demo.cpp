#include "Logger.hpp"
int main()
{
    std::thread t([](){
        for (;;)
        {
            auto spLogLine = std::move(log_helper::logger::logger_cache().wait_and_pop());
            spLogLine->test_print();
        }
    });
    t.detach();
	LOG(0, "%s + %s = %c", "1", "2", '3');
	LOG(0, "%s + %s = %c", "2", "2", '3');
	LOG(0, "%s + %s = %c", "3", "2", '3');
	LOG(0, "%s + %s = %c", "4", "2", '3');
    getchar();
    return 0;
}