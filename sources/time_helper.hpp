#pragma once
#include <chrono>
namespace utils
{
    namespace time_helper
    {
        /* Returns microseconds since epoch */
        inline uint64_t timestamp_now()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }
    }
}