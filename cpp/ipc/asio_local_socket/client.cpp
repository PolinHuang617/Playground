#include <cstring>
#include <string>
#include <chrono>
#include <memory>

#include <boost/asio.hpp>

#include "../utils.hpp"

int main(int argc, char const *argv[])
{
    using boost::asio::local::stream_protocol;
    try
    {
        boost::asio::io_context io_context;
        
        stream_protocol::socket sock(io_context);
        sock.connect(stream_protocol::endpoint("/tmp/asio_local_socket"));

        printf("Connected to server\n");

        std::unique_ptr<struct Data> data(new struct Data);

        size_t size = 0;
        size_t counter = 0;
        auto start = std::chrono::high_resolution_clock::now();
        while (counter < RUN_TIMES)
        {
            boost::asio::read(sock, boost::asio::buffer(data->buffer, BUFFER_LEN));
            size = strlen(data->buffer);
#ifdef DEBUG
            printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
            data->iSignal = 0;
            bzero(data->buffer, BUFFER_LEN);
            boost::asio::write(sock, boost::asio::buffer(data.get(), sizeof(data->iSignal)));

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
        
    return EXIT_SUCCESS;
}
