#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

constexpr std::chrono::seconds interval(1);

std::mutex mutex;
std::timed_mutex tmutex;

int job_shared = 0;  // 两个线程都能修改'job_shared',mutex将保护此变量
int job_exclusive = 0;  // 只有一个线程能修改'job_exclusive',不需要保护

// 此线程只能修改 'job_shared'
void job1_mutex()
{
    mutex.lock();

    std::this_thread::sleep_for(5 * interval);  // 令job1持锁等待
    ++job_shared;
    std::cout << "job1 shared (" << job_shared << ")" << std::endl;

    mutex.unlock();
}

// 此线程只能修改 'job_shared'
void job1_lock_guard()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::this_thread::sleep_for(5 * interval);  // 令job1持锁等待
    ++job_shared;
    std::cout << "job1 shared (" << job_shared << ")" << std::endl;
}

// 此线程只能修改 'job_shared'
void job1_lock_guard_tmutex()
{
    std::lock_guard<std::timed_mutex> lock(tmutex);
    std::this_thread::sleep_for(5 * interval);  // 令job1持锁等待
    ++job_shared;
    std::cout << "job1 shared (" << job_shared << ")" << std::endl;
}

// 此线程能修改'job_shared'和'job_exclusive'
void job2_mutex()
{
    while (true)  // 无限循环，直到获得锁并修改'job_shared'
    {
        if (mutex.try_lock())  // //尝试获得锁成功则修改'job_shared'
        {
            ++job_shared;
            std::cout << "job2 shared (" << job_shared << ")" << std::endl;
            mutex.unlock();
            break;
        }
        else  // //尝试获得锁失败,接着修改'job_exclusive'
        {
            ++job_exclusive;
            std::cout << "job2 exclusive (" << job_exclusive << ")" << std::endl;
            std::this_thread::sleep_for(interval);
        }
    }
}

// 此线程能修改'job_shared'和'job_exclusive'
void job2_unique_lock()
{
    while (true)  // 无限循环，直到获得锁并修改'job_shared'
    {
        std::unique_lock<std::mutex> ulock(mutex, std::try_to_lock);  // 以尝试锁策略创建智能锁
        if (ulock)  // //尝试获得锁成功则修改'job_shared'
        {
            ++job_shared;
            std::cout << "job2 shared (" << job_shared << ")" << std::endl;
            break;
        }
        else  // //尝试获得锁失败,接着修改'job_exclusive'
        {
            ++job_exclusive;
            std::cout << "job2 exclusive (" << job_exclusive << ")" << std::endl;
            std::this_thread::sleep_for(interval);
        }
    }
}

// 此线程能修改'job_shared'和'job_exclusive'
void job2_unique_lock_tmutex()
{
    while (true)  // 无限循环，直到获得锁并修改'job_shared'
    {
        std::unique_lock<std::timed_mutex> ulock(tmutex, std::defer_lock);  // 创建一个智能锁但先不锁定
        if (ulock.try_lock_for(3 * interval))  // 尝试获得锁成功则修改'job_shared'，尝试3*interval时长
        {
            ++job_shared;
            std::cout << "job2 shared (" << job_shared << ")" << std::endl;
            break;
        }
        else  // //尝试获得锁失败,接着修改'job_exclusive'
        {
            ++job_exclusive;
            std::cout << "job2 exclusive (" << job_exclusive << ")" << std::endl;
            std::this_thread::sleep_for(interval);
        }
    }
}


int main(int argc, char const *argv[])
{
    // std::thread th1(job1_mutex);
    std::thread th1(job1_lock_guard);
    // std::thread th1(job1_lock_guard_tmutex);
    // std::thread th2(job2_mutex);
    std::thread th2(job2_unique_lock);
    // std::thread th2(job2_unique_lock_tmutex);

    th1.join();
    th2.join();

    return 0;
}
