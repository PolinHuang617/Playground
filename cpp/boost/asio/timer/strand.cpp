#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
class Printer
{
private:
    int count_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
public:
    Printer(boost::asio::io_context& io_context);
    ~Printer();

    void print1();
    void print2();
};

Printer::Printer(boost::asio::io_context& io_context)
    : strand_(boost::asio::make_strand(io_context)),
      timer1_(io_context, boost::asio::chrono::seconds(1)),
      timer2_(io_context, boost::asio::chrono::seconds(1)),
      count_(0)
{
    timer1_.async_wait(boost::asio::bind_executor(strand_,
        boost::bind(&Printer::print1, this)));
    timer2_.async_wait(boost::asio::bind_executor(strand_,
        boost::bind(&Printer::print2, this)));
}

Printer::~Printer()
{
    std::cout << "Final count is " << count_ << std::endl;
}

void Printer::print1()
{
    if (count_ < 1000)
    {
        std::cout << "Timer 1: " << count_ << std::endl;
        ++count_;

        timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

        timer1_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&Printer::print1, this)));
    }
}

void Printer::print2()
{
    if (count_ < 1000)
    {
        std::cout << "Timer 2: " << count_ << std::endl;
        ++count_;

        timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

        timer2_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&Printer::print2, this)));
    }
}

int main(int argc, char const *argv[])
{
    boost::asio::io_context io_context;

    Printer printer(io_context);

    std::thread th(boost::bind(&boost::asio::io_context::run, &io_context));

    io_context.run();
    th.join();

    return 0;
}
