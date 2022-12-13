#include <iostream>
#include <random>

#include "thread_pool.hpp"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);

auto rnd = std::bind(dist, mt);

void simulate_hard_computation()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

void multiply(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

void multiply_output(int& out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl;
}

int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

void example()
{
    ThreadPool pool(3);

    pool.init();

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 10; ++j)
        {
            pool.submit(multiply, i, j);
        }
    }
    
    int output_ref;
    auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);
    future1.get();
    std::cout << "Last operation result is equals to " << output_ref << std::endl;

    auto future2 = pool.submit(multiply_return, 5, 3);
    int res = future2.get();
    std::cout << "Last operation result is equals to " << res << std::endl;

    pool.shutdown();
}

int main(int argc, char const *argv[])
{
    example();

    return 0;
}
