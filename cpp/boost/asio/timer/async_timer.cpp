#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

void print(const boost::system::error_code& error,
            boost::asio::steady_timer* timer,
            int* count)
{
    if (*count < 20)
    {
        std::cout << *count << std::endl;
        ++(*count);

        timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(1));
        timer->async_wait(boost::bind(
            print,
            boost::asio::placeholders::error(),
            timer,
            count));
    }
}

int main(int argc, char const *argv[])
{
    boost::asio::io_context io_context;
    boost::asio::steady_timer timer1(io_context, boost::asio::chrono::seconds(3));

    timer1.async_wait([=](const boost::system::error_code& error)
    {
        std::cout << "Hello world!" << std::endl;
    });

    int count = 0;
    boost::asio::steady_timer timer2(io_context, boost::asio::chrono::seconds(1));
    timer2.async_wait(boost::bind(print, 
        boost::asio::placeholders::error(), &timer2, &count));

    std::cout << "Waiting..." << std::endl;

    io_context.run();

    std::cout << "Final count is " << count << std::endl;

    return 0;
}
