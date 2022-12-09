#include <iostream>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char const *argv[])
{
    try
    {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);

        tcp::socket socket(io_context);
        boost::asio::connect(socket, resolver.resolve("0.0.0.0", "8000"));

        for (;;)
        {
            std::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
            {
                break;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }
            
            std::cout.write(buf.data(), len);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return EXIT_SUCCESS;
}
