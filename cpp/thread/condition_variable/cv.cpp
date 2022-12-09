#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mutex;
std::condition_variable cv;
std::vector<int> vec;

constexpr int productNum = 5;

void producer()
{
    for (size_t i = 1; i <= productNum; ++i)
    {
        std::unique_lock<std::mutex> ulock(mutex);
        while (!vec.empty())
        {
            cv.wait(ulock);  // vec不为空时阻塞
        }
        vec.emplace_back(i);
        vec.emplace_back(i+1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Producer produces No." << i << " product" << std::endl;
        cv.notify_all(); // 释放线程锁
    }
}

void consumer(const uint id)
{
    int product = 0;
    while (true)
    {
        std::unique_lock<std::mutex> ulock(mutex);
        while (vec.empty())
        {
            cv.wait(ulock);
        }
        product = vec.back();
        vec.pop_back();
        std::cout << "Consumer " << id << " consumes No." << product << " product" << std::endl;
        cv.notify_all();
    }
}

int main(int argc, char const *argv[])
{
    std::thread th1(producer);
    std::thread th2(consumer, 1);

    th1.join();
    th2.join();

    return 0;
}

