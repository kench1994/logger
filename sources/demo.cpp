#include "Logger.hpp"
int main()
{
	//utils::BlockingQueue<int> qu;
	//std::thread tt([&qu]() {
	//	for (;;)
	//	{
	//		auto T = qu.wait_and_pop();
	//		std::cout << T << std::endl;
	//	}
	//});
	//int i = 0;
	//while (1)
	//{
	//	std::cout << timestamp_now() << std::endl;
	//	qu.push(i++);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//}
	//tt.join();

    std::thread t([](){
        for (;;)
        {
            std::unique_ptr<log_helper::LogLine>spLogLine = log_helper::logger::logger_cache().wait_and_pop();
            spLogLine->test_print();
        }
    });
    t.detach();
	//LOG(0, "%s + %s = %c", "1", "2", '3');
	//LOG(0, "%s + %s = %c", "1", "2", '3');
	//LOG(0, "%s + %s = %c", "1", "2", '3');
	//LOG(0, "%s + %s = %c", "1", "2", '3');

    std::thread t2([]() {
        LOG(0, "%s + %s = %c", "1", "2", '3');
    });
	t2.detach();
	std::thread t3([]() {
		LOG(0, "%s + %s = %c", "1", "2", '3');
		});
	t3.detach();
    getchar();
    return 0;
}