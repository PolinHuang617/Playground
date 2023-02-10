#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <memory>
#include <vector>
#include <ostream>
#include <iostream>

#include "list_node.hpp"

template <typename T>
class ForwardList
{
public:
    ForwardList() : m_head(new ListNode<T>()) {}
    ~ForwardList() = default;

    ForwardList(const ListNode<T>* list);

    ForwardList(const std::vector<T>& list);

    friend std::ostream& operator<< (std::ostream& out, const ForwardList<T>& list);

    // Insert
    bool insertAtHead(const std::shared_ptr<ListNode<T> > node);
    // AtRear
    bool insertAtRear(const std::shared_ptr<ListNode<T> > node);

    // Delete
    bool deleteValue(const T val);
    bool deleteAt(const size_t pos);

    // Update
    bool updateAt(const size_t pos);

    // Search for element
    T search(const size_t pos);


private:
    std::shared_ptr<ListNode<T> > m_head;
};

template <typename T>
ForwardList<T>::ForwardList(const std::vector<T>& list)
{
    using std::cerr;
    using std::endl;
    using std::shared_ptr;

    for (const auto& item : list)
    {
        shared_ptr<ListNode<T> > p_node(new ListNode<T>(item));
        bool res = insertAtRear(p_node);
        if (!res)
        {
            cerr << "Insert element at rear error" << endl;
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ForwardList<T>& list)
{
    using std::cout;
    using std::endl;

    if (list.m_head == nullptr)
    {
        cout << "Empty list" << endl;
        return out;
    }

    for (ListNode<T>* p = list.m_head->getNext(); p != nullptr; p = p->getNext())
    {
        cout << p->getValue() << " ";
    }
    cout << endl;

    return out;
}

template <typename T>
bool ForwardList<T>::insertAtRear(const std::shared_ptr<ListNode<T> > node)
{
    using std::shared_ptr;

    shared_ptr<ListNode<T> > head = m_head;
    node->setNext(head->getNext());
    head->setNext(node);
}

#endif
