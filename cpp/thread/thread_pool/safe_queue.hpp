#pragma once

#include <queue>
#include <mutex>

template <typename T>
class SafeQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

public:
    SafeQueue() {}
    SafeQueue(SafeQueue&& other) {}
    ~SafeQueue() {}

    bool empty();
    int size();
    void enqueue(T& t);
    bool dequeue(T& t);
};

template <typename T>
bool SafeQueue<T>::empty()
{
    std::unique_lock<std::mutex> ulock(m_mutex);
    return m_queue.empty();
}

template <typename T>
int SafeQueue<T>::size()
{
    std::unique_lock<std::mutex> ulock(m_mutex);
    return m_queue.size();
}

template <typename T>
void SafeQueue<T>::enqueue(T& t)
{
    std::unique_lock<std::mutex> ulock(m_mutex);
    m_queue.emplace(t);
}

template <typename T>
bool SafeQueue<T>::dequeue(T& t)
{
    std::unique_lock<std::mutex> ulock(m_mutex);
    
    if (m_queue.empty())
    {
        return false;
    }
    t = std::move(m_queue.front());
    m_queue.pop();
    
    return true;
}