#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <vector>
#include "Node.h"

template <typename ValueType, typename KeyType = unsigned long int>
class SkipList {
public:
    class iterator {
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef Node<ValueType, KeyType> value_type;
        typedef long int difference_type;
        typedef Node<ValueType, KeyType>* pointer;
        typedef Node<ValueType, KeyType> reference;
    public:
        iterator(Node<ValueType, KeyType> d) : data(d)
        {}
        iterator(iterator const& rha) : data(rha.data)
        {}
        iterator operator=(iterator const& lha)
        {
            if (&lha == this)
            {
                return *this;
            }
            data = lha.data;
            return *this;
        }

        bool operator==(iterator const& lha) {
            return data.key == lha.data.key;
        }
        bool operator!=(iterator const& lha) {
            return data.key != lha.data.key;
        }

        Node<ValueType, KeyType> operator*() {
            return data;
        }
        Node<ValueType, KeyType>* operator->() {
            return &data;
        }

        iterator& operator++() {         // prefix
            data = *data.forward[0];
            return *this;
        }

        iterator operator++(int) {
            iterator res(*this);
            ++(*this);
            return res;
        }

    private:
        Node<ValueType, KeyType> data;
    };

    iterator begin() {
        return iterator(*head->forward[0]);
    }

    iterator end() {
        return iterator(NIL);
    }

    SkipList(size_t max_level=10) : max_level(max_level), level(0), NIL(), gen(seed), length(0) {
        head = new Node<ValueType>(0, NULL, max_level);
        for (size_t i = 0; i < max_level; i++)
        {
            head->forward[i] = &NIL;
        }
    }

    template <typename T>
    SkipList(T st, T en, size_t max_level = 10) : max_level(max_level), level(0), NIL(), gen(seed), length(0) {
        head = new Node<ValueType>(0, NULL, max_level);
        for (size_t i = 0; i < max_level; i++)
        {
            head->forward[i] = &NIL;
        }
        for (auto it = st; it != en; it++)
        {
            Insert(it->key, it->value);
        }
    }

    SkipList(SkipList<ValueType, KeyType>& rha) : gen(seed), NIL(rha.NIL), level(0), length(0),
        max_level(rha.max_level) {
        head = new Node<ValueType>(0, NULL, max_level);
        for (size_t i = 0; i < max_level; i++)
        {
            head->forward[i] = &NIL;
        }
        for (auto it = rha.begin(); it != rha.end(); ++it)
        {
            Insert(it->key, it->value);
        }
    }

    SkipList<ValueType, KeyType>& operator=(SkipList<ValueType, KeyType>& rha) {
        if (&rha == this)
        {
            return *this;
        }

        clear();
        delete head;

        gen.seed(seed);
        NIL = rha.NIL;
        level = 0;
        length = 0;
        max_level = rha.max_level;

        head = new Node<ValueType>(0, NULL, max_level);
        for (size_t i = 0; i < max_level; i++)
        {
            head->forward[i] = &NIL;
        }
        for (auto it = rha.begin(); it != rha.end(); it++)
        {
            Insert(it->key, it->value);
        }

        return *this;
    }

    SkipList(SkipList<ValueType, KeyType>&& rha) : gen(rha.gen), NIL(), level(rha.level), length(rha.length),
        max_level(rha.max_level) {
        head = rha.head;
        rha.gen.seed(seed);

        rha.head = new Node<ValueType>(0, NULL, rha.max_level);
        for (size_t i = 0; i < rha.max_level; i++)
        {
            rha.head->forward[i] = &NIL;
        }
        rha.level = 0;
        rha.length = 0;
        std::swap(NIL, rha.NIL);
    }

    SkipList<ValueType, KeyType>& operator=(SkipList<ValueType, KeyType>&& rha) {
        if (&rha == this)
        {
            return;
        }

        clear();
        delete head;

        gen = rha.gen;
        level = rha.level;
        length = rha.length;
        max_level = rha.max_level;

        head = rha.head;
        std::swap(gen, rha.gen);

        rha.head = new Node<ValueType>(0, NULL, rha.max_level);
        for (size_t i = 0; i < rha.max_level; i++)
        {
            rha.head->forward[i] = &NIL;
        }
        rha.level = 0;
        rha.length = 0;
        std::swap(NIL, rha.NIL);

        return *this;
    }

    void Insert(KeyType k, ValueType new_value) {
        std::vector<Node<ValueType, KeyType>*> ptrs(max_level);
        Node<ValueType, KeyType>* tmp = head;
        for (size_t i = level; i > 0; i--)
        {
            while (tmp->forward[i-1]->key < k) tmp = tmp->forward[i-1];
            ptrs[i-1] = tmp;
        }
        tmp = tmp->forward[0];
        if (tmp->key == k) tmp->value = new_value;
        else {
            size_t lvl = randomLevel();
            if (lvl > level - 1 or level == 0) {
                for (size_t i = level; i < lvl + 1; i++)
                {
                    ptrs[i] = head;
                }
                level = lvl + 1;
            }
            tmp = new Node<ValueType>(k, new_value, lvl + 1);
            for (size_t i = 0; i < lvl + 1; i++)
            {
                tmp->forward[i] = ptrs[i]->forward[i];
                ptrs[i]->forward[i] = tmp;
            }
            length++;
        }
    }

    template <typename T>
    void Insert(T st, T en) {
        for (auto it = st; it != en; it++)
        {
            Insert(it->key, it->value);
        }
    }

    void Delete(KeyType k) {
        std::vector<Node<ValueType, KeyType>*> ptrs(max_level);
        Node<ValueType, KeyType>* tmp = head;
        for (size_t i = level; i > 0; i--)
        {
            while (tmp->forward[i - 1]->key < k) tmp = tmp->forward[i - 1];
            ptrs[i - 1] = tmp;
        }
        tmp = tmp->forward[0];
        if (tmp->key == k) {
            length--;
            for (size_t i = 0; i < level; i++)
            {
                if (ptrs[i]->forward[i] != tmp) break;
                ptrs[i]->forward[i] = tmp->forward[i];
            }
            delete tmp;
            while (level > 0 and head->forward[level - 1] == &NIL) level--;
        }
    }

    iterator Find(KeyType k) {
        Node<ValueType, KeyType>* tmp = head;
        for (size_t i = level; i > 0; i--)
        {
            while (tmp->forward[i - 1]->key < k) tmp = tmp->forward[i - 1];
        }
        tmp = tmp->forward[0];
        if (tmp->key == k) return iterator(*tmp);
        else return end();
    }

    bool empty() {
        return level == 0 and length == 0;
    }

    size_t count(KeyType k) {
        size_t res = 0;
        for (auto it = begin(); it != end(); ++it) if (it->key == k) res++;
        return res;
    }

    iterator lower_bound(KeyType k) {
        for (auto it = begin(); it != end(); ++it) if (it->key >= k) return it;
        return end();
    }

    iterator upper_bound(KeyType k) { 
        for (auto it = begin(); it != end(); ++it) if (it->key > k) return it;
        return end();
    }

    void clear() {
        while (head->forward[0] != &NIL) Delete(head->forward[0]->key);
    }

    void erase(iterator iter) {
        Delete(iter->key);
    }

    void erase(iterator it_s, iterator  it_e) {
        for (auto it = it_s; it != it_e; it++)
        {
            Delete(it->key);
        }
    }

    size_t size() {
        return length;
    }

    ~SkipList() {
        clear();
        delete head;
    }

private:
    size_t randomLevel()
    {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        size_t level = 0;
        double res = distribution(gen);
        while (res < 0.5 and level < max_level - 1) { 
            level++;
            res = distribution(gen);
        }
        return level;
    }

    Node<ValueType, KeyType>* get_head() {
        return head;
    }
    
    size_t length;
    size_t seed = 9996;
    std::mt19937 gen;
    Node<ValueType, KeyType> NIL;
    size_t level;
    size_t max_level;
    Node<ValueType, KeyType>* head;
};
