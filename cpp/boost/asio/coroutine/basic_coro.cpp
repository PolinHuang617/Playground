#include <ctime>
#include <chrono>
#include <iostream>
#include <boost/fiber/all.hpp>

void say_after(unsigned int delay, const char* what)
{
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    std::cout << what << std::endl;
}

int main(int argc, char const *argv[])
{
    time_t now = time(0);
    std::cout << "started at " << ctime(&now);

    boost::fibers::fiber fibier1(say_after, 5, "hello");
    boost::fibers::fiber fibier2(say_after, 10, "world");

    fibier1.join();
    fibier2.join();

    now = time(0);
    std::cout << "finished at " << ctime(&now);

    return 0;
}
