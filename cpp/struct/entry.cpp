#include <iostream>

struct OrderField
{
    int id;
    char* name;
};


int main(int argc, char const *argv[])
{
    OrderField* orders = new OrderField[10];

    orders[0].id = 1;
    orders[0].name = "asd";
    orders[1].id = 2;
    orders[1].name = "aflawef";
    orders[2].id = 3;
    orders[2].name = "r230rf02q";

    std::cout << sizeof(orders) << std::endl;
    std::cout << (orders+sizeof(orders))->id << std::endl;

    delete[] orders;
    orders = nullptr;

    return 0;
}
