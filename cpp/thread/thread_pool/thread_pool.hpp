#pragma once

#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>

#include "safe_queue.hpp"

class ThreadPool
{
private:
    class ThreadWorker
    {
    private:
        int m_id;
        ThreadPool* m_pool;
    public:
        ThreadWorker(ThreadPool* pool, const int id) 
            : m_pool(pool),
              m_id(id) {}

        ~ThreadWorker() {}

        void operator()();
    };
    
public:
    ThreadPool(const int n_threads = 4) 
        : m_threads(std::vector<std::thread>(n_threads)),
          m_shutdown(false) {}

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    ~ThreadPool() {}

    void init();
    void shutdown();
    
    template <typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

private:
    bool m_shutdown;
    SafeQueue<std::function<void()>> m_queue;
    std::vector<std::thread> m_threads;
    std::mutex m_conditional_mutex;
    std::condition_variable m_conditional_lock;
};

void ThreadPool::ThreadWorker::operator()()
{
    std::function<void()> func;

    bool dequeued;

    while (!m_pool->m_shutdown)
    {
        std::unique_lock<std::mutex> ulock(m_pool->m_conditional_mutex);
        if (m_pool->m_queue.empty())
        {
            m_pool->m_conditional_lock.wait(ulock);
        }
        
        dequeued = m_pool->m_queue.dequeue(func);
        if (dequeued)
        {
            func();
        }
    }
}

void ThreadPool::init()
{
    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads.at(i) = std::thread(ThreadWorker(this, i));
    }
}

void ThreadPool::shutdown()
{
    m_shutdown = true;
    m_conditional_lock.notify_all();

    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        if (m_threads.at(i).joinable())
        {
            m_threads.at(i).join();
        }
    }
}

template <typename F, typename... Args>
auto ThreadPool::submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
{
    std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    std::function<void()> wrapped_func = [task_ptr]()
    {
        (*task_ptr)();
    };

    m_queue.enqueue(wrapped_func);
    m_conditional_lock.notify_one();

    return task_ptr->get_future();
}
