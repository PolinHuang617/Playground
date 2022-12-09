#include <iostream>
#include <chrono>
#include <future>
#include <numeric>
#include <vector>

void accumulate(const std::vector<int>::iterator& begin,
                const std::vector<int>::iterator& end,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(begin, end, 0);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    accumulate_promise.set_value(sum);
}

int main(int argc, char const *argv[])
{
    // 使用promise<int>在线程之间传递结果
    std::vector numbers = {1, 2, 3, 4, 5, 6};
    std::promise<int> accumulate_promise;
    std::future accumulate_future = accumulate_promise.get_future();
    std::thread th(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    // accumulate_future.wait();  // Can be ignored
    std::cout << "result=" << accumulate_future.get() << std::endl;
    th.join();    
    
    return 0;
}
