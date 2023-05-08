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
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8000));
    tcp::socket socket(io);

    std::cout << "等待客户端连接...\n";
    acceptor.accept(socket);

    std::cout << "客户端已连接\n";

    // 接收数据包
    size_t loginFieldSize = sizeof(LoginField);
    size_t netPackageSize = sizeof(net_package) + loginFieldSize;
    char *buffer = new char[netPackageSize];
    boost::asio::read(socket, boost::asio::buffer(buffer, netPackageSize));

    net_package *package = reinterpret_cast<net_package *>(buffer);
    std::cout << package->data_size << std::endl;
    std::cout << package->data_type << std::endl;

    // 解析数据包
    LoginField login_field;
    memcpy(&login_field, package->data_buf, package->data_size);

    std::cout << "账号: " << login_field.strategy_account << "\n";
    std::cout << "密码: " << login_field.strategy_password << "\n";
    delete[] buffer;

    return 0;
}
