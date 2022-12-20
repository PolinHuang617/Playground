#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

constexpr int MAX_LENGTH = 1024;

void session(tcp::socket sock) {
    try {
        while (true) {
            char data[MAX_LENGTH];
            
            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) {
                break;  // Connection closed cleanly by peer
            } else if (error) {
                // Some other error
                throw boost::system::system_error(error);
            }

            boost::asio::write(sock, boost::asio::buffer(data, length));
            std::cout << data << std::endl;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void server(boost::asio::io_context& io_context, unsigned short port) {
    tcp::acceptor acpt(io_context, tcp::endpoint(tcp::v4(), port));
    while (true) {
        std::thread(session, acpt.accept()).detach();
    }
}

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;
        
        server(io_context, 8001);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
