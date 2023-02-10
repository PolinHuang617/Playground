#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>

using std::shared_ptr;

template <typename T>
class ListNode
{
public:
    ListNode(T value = 0) : m_value(value), m_next(nullptr) {}
    ~ListNode() = default;

    inline T getValue() { return m_value; }
    inline void setValue(T val) { m_value = val; }

    inline shared_ptr<ListNode<T> > getNext() { return m_next; }
    inline void setNext(shared_ptr<ListNode<T> > next) { m_next = next; }

private:
    T m_value;
    std::shared_ptr<ListNode<T> > m_next;
};

#endif