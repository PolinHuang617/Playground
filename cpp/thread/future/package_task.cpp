#include <iostream>
#include <chrono>
#include <future>
#include <numeric>
#include <vector>
#include <utility>

int accumulate(const std::vector<int>::iterator& begin,
               const std::vector<int>::iterator& end)
{
    int sum = std::accumulate(begin, end, 0);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return sum;
}

int main(int argc, char const *argv[])
{
    std::vector numbers = {1, 2, 3, 4, 5, 6};
    std::packaged_task<int(const std::vector<int>::iterator&, const std::vector<int>::iterator&)> accumulate_task(accumulate);
    std::future accumulate_future = accumulate_task.get_future();
    std::thread th(std::move(accumulate_task), numbers.begin(), numbers.end());
    // accumulate_future.wait();  // Can be ignored
    std::cout << "result=" << accumulate_future.get() << std::endl;
    th.join();    
    
    return 0;
}
