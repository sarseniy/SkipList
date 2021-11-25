#pragma once

#include <vector>


template <typename ValueType, typename KeyType = unsigned long int>
struct Node
{
    Node() : Node(0x7fffffff, nullptr, 0)
    {}

    Node(size_t level) : Node(0x7fffffff, nullptr, level)
    {}

    Node(KeyType key, ValueType value) : Node(key, value, 0)
    {}

    Node(KeyType key, ValueType value, size_t level) : key(key), value(value), forward{ level }
    {}

    KeyType key;
    ValueType value;
    std::vector<Node<ValueType, KeyType>*> forward;
};
