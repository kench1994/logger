#pragma once
#include <vector>
#include <boost/any.hpp>
namespace utils
{
    struct ParamPacker {
        ParamPacker() {}
        ~ParamPacker() {}

        void pack()
        {}

        void pack(const boost::any& t)
        {
            vParams.push_back(t);
        }

        void pack(boost::any&& t)
        {
            vParams.emplace_back(t);
        }

        template<typename ... Args>
        void pack(const boost::any& t, const Args& ... args)
        {
            vParams.push_back(t);
            if (!sizeof...(args))
                return;
            pack(args ...);
        }

        template<typename ... Args>
        void pack(boost::any&& t, Args&& ... args)
        {
            vParams.emplace_back(t);
            if (!sizeof...(args))
                return;
            pack(std::forward<Args>(args)...);
        }

        std::vector<boost::any> vParams;
    };
}