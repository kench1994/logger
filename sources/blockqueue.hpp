#pragma once
#include <mutex>
#include <queue>
#include <memory>
#include <thread>
#include <assert.h>
#include <condition_variable>
namespace utils
{
    template<typename T>
    class BlockingQueue// : noncopyable
    {
    public:
        using queue_type = std::queue<T>;

        BlockingQueue()
        {
        }

        ~BlockingQueue()
        {
            
        }

        void push(const T& x)
        {
            std::unique_lock lock(m_mtx);
            m_queue.push(x);
            m_mtx.notify();
        }

        void push(T&& x)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            m_queue.push(std::move(x));
            m_Condit.notify_one();
        }

        T wait_and_pop()
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            /*
            wait()�����������ĳ�Ա������������һ������������ڶ�������lambda���ʽ����ֵ��false����ôwait��������һ�����������������������������С�
            ������ʲôʱ���أ�����������ĳ���̵߳���notify_one������Ա����Ϊֹ���������true����ôwait()ֱ�ӷ��ء�
            ���û�еڶ����������͸�Ĭ�ϵڶ�����������falseЧ��һ����

            my_cond.notify_one();//���԰�wait���̻߳��ѣ�ִ�������У�wait�ͱ�������
            ֻ��֪ͨһ���̣߳���������̸߳ɵĲ�ͬ�����飬������wait����ô���Ѷ���̣߳�notify_all���������߳�ֻ��һ���߳��ܻ�ȡ��������һ��û�õ�������һֱ���ϵ�ȥ�����

            ������notify_one()��wait����֮��wait���ϳ��Ի�ȡ���������������ȡ���������̾Ϳ���wait������Ż�ȡ�������ȡ���ˣ�wait�ͻ�ȡ�������͵�����������
            ��1�����wait�еڶ���������lambda��,���ж�������ʽ�����lambdaΪfalse����ô�������ϣ������ߣ��ٵȴ����ѣ�
            ��2��������ʽΪtrue����ôwait���أ���������������ʱ���������������ŵģ�������ֻҪ���ߵ��������������������һ�������ŵġ�
            ��3�����û�еڶ���������wait�ͷ��أ�����������
            */
            m_Condit.wait(lock);
            assert(!m_queue.empty());
            T front(std::move(m_queue.front()));
            m_queue.pop();
            return front;
        }

        queue_type drain()
        {
            queue_type queue;
            {
                std::unique_lock<std::mutex> lock(m_mtx);
                queue = std::move(m_queue);
                assert(m_queue.empty());
            }
            return queue;
        }

        size_t size() const
        {
            std::unique_lock lock(m_mtx);
            return m_queue.size();
        }

    private:
        std::condition_variable m_Condit;
        mutable std::mutex m_mtx;
        queue_type m_queue;
    };
}