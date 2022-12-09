#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char const *argv[])
{
    boost::asio::io_context io_context;
    boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(3));

    timer.wait();

    std::cout << "Hello world!" << std::endl;

    return 0;
}
