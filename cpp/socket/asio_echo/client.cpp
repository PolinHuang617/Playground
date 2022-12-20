#include <cstdlib>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

constexpr int MAX_LENGTH = 1024;

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(s, resolver.resolve("127.0.0.0", "8001"));

        std::cout << "Enter message: ";
        char request[MAX_LENGTH];
        std::cin.getline(request, MAX_LENGTH);
        size_t request_length = std::strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[MAX_LENGTH];
        size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return EXIT_SUCCESS;
}
