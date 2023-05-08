#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

#pragma pack(1)
struct LoginField
{
    char strategy_account[64];
    char strategy_password[256];
};

struct net_package
{
    int32_t data_size;
    int32_t data_type;
    char *data_buf[];
};
#pragma pack()

int main()
{
    io_service io;
    tcp::resolver resolver(io);
    tcp::resolver::query query("localhost", "8000");
    tcp::socket socket(io);

    connect(socket, resolver.resolve(query));

    std::cout << "已连接服务器\n";

    // 组装数据包
    LoginField loginField {"123", "456"};
    size_t loginFieldSize = sizeof(LoginField);
    size_t netPackageSize = sizeof(net_package) + loginFieldSize;
    char *buffer = new char[netPackageSize];
    net_package *package = reinterpret_cast<net_package *>(buffer);
    package->data_size = loginFieldSize;
    package->data_type = 1; // 假设数据类型为0
    memcpy(package->data_buf, &loginField, loginFieldSize);

    boost::asio::write(socket, boost::asio::buffer(buffer, netPackageSize));

    std::cout << "数据已发送\n";

    socket.close();

    delete[] buffer;

    return 0;
}
