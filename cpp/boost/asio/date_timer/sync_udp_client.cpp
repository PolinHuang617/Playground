#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char const *argv[])
{
    try
    {
        boost::asio::io_context io_context;
        udp::resolver resolver(io_context);
        udp::endpoint recv_endpoint = 
            *resolver.resolve("0.0.0.0", "8000").begin();
        
        udp::socket socket(io_context);
        socket.open(udp::v4());

        boost::array<char, 1> send_buf = {{ 0 }};
        socket.send_to(boost::asio::buffer(send_buf), recv_endpoint);

        boost::array<char, 128> recv_buf;
        udp::endpoint send_endpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), send_endpoint);

        std::cout.write(recv_buf.data(), len);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
