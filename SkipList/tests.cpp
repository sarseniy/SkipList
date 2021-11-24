#pragma once
#include "SkipList.h"
#include "multiSkipList.h"

class Error {
public:
    void virtual perr() = 0;
    ~Error() {

    }
};

class ConstructorAndInsertError : public Error {
public:
    void perr() override {
        std::cout << "Constructor or Insert failure\n";
    }
};

class CopyError : public Error {
public:
    void perr() override {
        std::cout << "Copy failure\n";
    }
};

class IterConstructorError : public Error {
public:
    void perr() override {
        std::cout << "Iterator constructor failure\n";
    }
};

class EmptyError : public Error {
public:
    void perr() override {
        std::cout << "empty() method failure\n";
    }
};

class SizeError : public Error {
public:
    void perr() override {
        std::cout << "size() method failure\n";
    }
};

class IterInsertError : public Error {
public:
    void perr() override {
        std::cout << "Iteraror Insert failure\n";
    }
};

class IterError : public Error {
public:
    void perr() override {
        std::cout << "Iterator failure\n";
    }
};

class FindError : public Error {
public:
    void perr() override {
        std::cout << "find() failure\n";
    }
};

class CountError : public Error {
public:
    void perr() override {
        std::cout << "count() failure\n";
    }
};

class LowerUpperBoundError : public Error {
public:
    void perr() override {
        std::cout << "LowerUpperBound failure\n";
    }
};

class ClearError : public Error {
public:
    void perr() override {
        std::cout << "clear() error\n";
    }
};

class EraseError : public Error {
public:
    void perr() override {
        std::cout << "erase() error\n";
    }
};

class multiSkipListError : public Error {
public:
    void perr() override {
        std::cout << "multiSkipList stuff failed\n";
    }
};

inline void ConstructorAndInsertTest() {
    bool flag = true;
    SkipList<int> f;
    flag = (f.size() == 0) ? true : false;
    f.clear();
    flag = (f.size() == 0) ? true : false;

    f.Insert(85ul, 66);
    f.Insert(77ul, 32);
    f.Insert(2ul, 97);
    f.Insert(50ul, 37);

    auto it = f.begin();
    flag = (it->value == 97) ? true : false;
    it++;
    flag = (it->value == 37) ? true : false;
    it++;
    flag = (it->value == 32) ? true : false;
    it++;
    flag = (it->value == 66) ? true : false;

    flag = (f.size() == 4) ? true : false;

    f.Insert(77ul, 99);
    flag = (f.size() == 4) ? true : false;

    ConstructorAndInsertError err;
    if (!flag) throw(err);
}

inline void CopyTest() {
    bool flag = true;

    SkipList<int> f;
    f.Insert(85ul, 66);
    f.Insert(77ul, 32);
    f.Insert(2ul, 97);
    f.Insert(50ul, 37);

    SkipList<int> g = f;

    flag = (f.size() == g.size()) ? true : false;

    auto it2 = g.begin();
    for (auto it = f.begin(); it != f.end(); it++) {
        flag = (it->value == it2->value and it->key == it2->key) ? true : false;
        it2++;
    }

    g.Insert(2ul, 999);
    f = g;

    flag = (f.size() == g.size()) ? true : false;

    it2 = g.begin();
    for (auto it = f.begin(); it != f.end(); it++) {
        flag = (it->value == it2->value and it->key == it2->key) ? true : false;
        it2++;
    }

    IterConstructorError err;
    if (!flag) throw(err);
}

inline void IterConstructorTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    flag = (f.size() == a.size()) ? true : false;
    flag = ((++f.begin())->key == 24) ? true : false;
    flag = ((++f.begin())->value == 2) ? true : false;

    IterConstructorError err;
    if (!flag) throw(err);
}

inline void EmptyTest() {
    bool flag = true;

    SkipList<int> f;

    flag = (f.empty() == true) ? true : false;

    f.Insert(56ul, 7);
    flag = (f.empty() == false) ? true : false;
    f.clear();
    flag = (f.empty() == true) ? true : false;

    EmptyError err;
    if (!flag) throw(err);
}

inline void SizeTest() {
    bool flag = true;

    SkipList<int> f;

    flag = (f.size() == 0) ? true : false;

    f.Insert(56ul, 7);
    flag = (f.size() == 1) ? true : false;
    f.Insert(56ul, 123);
    flag = (f.size() == 1) ? true : false;
    f.Insert(78ul, 123);
    flag = (f.size() == 2) ? true : false;

    f.clear();
    flag = (f.size() == 0) ? true : false;

    SizeError err;
    if (!flag) throw(err);
}

inline void IterInsertTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f;

    f.Insert(54ul, 96);
    f.Insert(87ul, 11);
    flag = (f.size() == 2) ? true : false;
    f.Insert(a.begin(), a.end());
    flag = (f.size() == 6) ? true : false;
    flag = ((++f.begin())->key == 24) ? true : false;
    flag = ((++f.begin())->value == 2) ? true : false;

    IterInsertError err;
    if (!flag) throw(err);
}

inline void IterTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    auto it = f.begin();
    flag = (it->key == 3) ? true : false;
    flag = (it->value == 33) ? true : false;
    it++;
    flag = (it->key == 24) ? true : false;
    flag = (it->value == 2) ? true : false;
    it++;
    flag = (it->key == 74) ? true : false;
    flag = (it->value == 35) ? true : false;
    it++;
    flag = (it->key == 567) ? true : false;
    flag = (it->value == 1) ? true : false;
    it++;
    flag = (it == f.end()) ? true : false;

    IterError err;
    if (!flag) throw(err);
}

inline void FindTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    auto it = f.Find(4444);
    flag = (it == f.end()) ? true : false;

    it = f.Find(3);
    flag = (it == f.begin()) ? true : false;

    it = f.Find(567);
    flag = (it->value == 1) ? true : false;

    FindError err;
    if (!flag) throw(err);
}

inline void CountTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    size_t c = f.count(4444);
    flag = (c == 0) ? true : false;

    c = f.count(3);
    flag = (c == 1) ? true : false;

    c = f.count(567);
    flag = (c == 1) ? true : false;

    for (size_t i = 100; i < 200; i++)
    {
        flag = (f.count(i) == 0) ? true : false;
    }

    CountError err;
    if (!flag) throw(err);
}

inline void LowerUpperBoundTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    auto it = f.lower_bound(74);
    flag = (it->key == 74) ? true : false;
    flag = (it->value == 35) ? true : false;
    it = f.upper_bound(74);
    flag = (it->key == 567) ? true : false;
    flag = (it->value == 1) ? true : false;

    LowerUpperBoundError err;
    if (!flag) throw(err);
}

inline void ClearTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    flag = (f.size() == 4) ? true : false;
    f.clear();
    flag = (f.size() == 0) ? true : false;
    flag = (f.begin() == f.end()) ? true : false;

    LowerUpperBoundError err;
    if (!flag) throw(err);
}

inline void EraseTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    SkipList<int> f(a.begin(), a.end());

    auto it = f.begin();
    it++;

    f.erase(f.begin());
    flag = (f.begin() == it) ? true : false;

    it++;
    it++;
    f.erase(f.begin(), it);
    flag = (f.begin()->value == 1) ? true : false;
    flag = (f.size() == 1) ? true : false;

    f.erase(it, f.end());
    flag = (f.begin() == f.end()) ? true : false;
    flag = (f.size() == 0) ? true : false;



    EraseError err;
    if (!flag) throw(err);
}

inline void multiSkipListTest() {
    bool flag = true;

    std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };

    multiSkipList<int> f(a.begin(), a.end());

    f.Insert(24ul, 96);
    f.Insert(24ul, 145);
    f.Insert(24ul, 12312);
    f.Insert(24ul, 44);

    auto p = f.equal_range(24);
    flag = (f.size() == 8) ? true : false;
    flag = (f.count(24) == 5) ? true : false;
    f.erase(p.first, p.second);
    flag = (f.size() == 3) ? true : false;
    flag = (f.count(24) == 0) ? true : false;
    flag = (f.Find(24) == f.end()) ? true : false;

    multiSkipListError err;
    if (!flag) throw(err);
}

inline void TEST() {
    try
    {
        ConstructorAndInsertTest();
        CopyTest();
        IterConstructorTest();
        EmptyTest();
        SizeTest();
        IterInsertTest();
        IterTest();
        FindTest();
        CountTest();
        LowerUpperBoundTest();
        EraseTest();
        multiSkipListTest();
    }
    catch (ConstructorAndInsertError err)
    {
        err.perr();
    }
    catch (IterConstructorError err)
    {
        err.perr();
    }
    catch (CopyError err)
    {
        err.perr();
    }
    catch (EmptyError err)
    {
        err.perr();
    }
    catch (SizeError err)
    {
        err.perr();
    }
    catch (IterInsertError err)
    {
        err.perr();
    }
    catch (IterError err)
    {
        err.perr();
    }
    catch (FindError err)
    {
        err.perr();
    }
    catch (CountError err)
    {
        err.perr();
    }
    catch (LowerUpperBoundError err)
    {
        err.perr();
    }
    catch (EraseError err)
    {
        err.perr();
    }
    catch (multiSkipListError err)
    {
        err.perr();
    }
    catch (...)
    {
        std::cout << "Something else went wrong...\n";
    }
}