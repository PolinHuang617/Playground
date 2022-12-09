#include <cstring>
#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "../utils.hpp"

int main(int argc, char const *argv[])
{
    using boost::asio::ip::tcp;
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acpt(io_context, tcp::endpoint(tcp::v4(), PORT));
        tcp::socket clientSocket = acpt.accept();

        std::unique_ptr<struct Data> data(new struct Data);
        data->iSignal = 0;
        strcpy(data->buffer, message.c_str());
        for (size_t i = 0; i < (BUFFER_LEN / message.size() - 1); ++i)
        {
            strcat(data->buffer, message.c_str());
        }

        size_t counter = 0;
        while (counter < RUN_TIMES)
        {
            if (data->iSignal != 1)
            {
                data->iSignal = 1;
                boost::asio::write(clientSocket, boost::asio::buffer(data->buffer, BUFFER_LEN));
#ifdef DEBUG
                printf("[%ld] write text (%ld bytes) to socket: %s\n", counter, strlen(data->buffer), data->buffer);
#endif
                ++counter;
            }
            boost::asio::read(clientSocket, boost::asio::buffer(data.get(), sizeof(data->iSignal)));
        }
    }
    catch(const std::exception& e)
    {
        perror(e.what());
        return EXIT_FAILURE;
    }
    
    return 0;
}

