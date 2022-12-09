#include <cstring>
#include <string>
#include <chrono>
#include <memory>

#include <boost/asio.hpp>

#include "../utils.hpp"

int main(int argc, char const *argv[])
{
    using boost::asio::ip::tcp;
    try
    {
        boost::asio::io_context io_context;
        
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("192.168.218.6"), PORT));

        printf("Connected to server\n");

        std::unique_ptr<struct Data> data(new struct Data);

        size_t size = 0;
        size_t counter = 0;
        auto start = std::chrono::high_resolution_clock::now();
        while (counter < RUN_TIMES)
        {
            boost::asio::read(socket, boost::asio::buffer(data->buffer, BUFFER_LEN));
            size = strlen(data->buffer);
#ifdef DEBUG
            printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
            data->iSignal = 0;
            bzero(data->buffer, BUFFER_LEN);
            boost::asio::write(socket, boost::asio::buffer(data.get(), sizeof(data->iSignal)));

            ++counter;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start);
        printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());
    }
    catch(const std::exception& e)
    {
        perror(e.what());
        return EXIT_FAILURE;
    }

    return 0;
}
