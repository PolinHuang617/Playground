#include <iostream>
#include <memory>

#include "list_node.hpp"
#include "forward_list.hpp"

int main(int argc, char* argv[])
{
    std::shared_ptr< ListNode<int> > head(new ListNode<int>(200));

    std::cout << head->getValue() << std::endl;

    ForwardList<int> list({1, 2, 3});

    return 0;
}
