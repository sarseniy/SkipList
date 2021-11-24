#include "SkipList.cpp"
#include "multiSkipList.cpp"



int main()
{
    {
        SkipList<int> f;
        f.Insert(85ul, 66);
        f.Insert(77ul, 32);
        f.Insert(2ul, 97);
        f.Insert(50ul, 37);

        SkipList<int> g = f;
        g.Insert(2ul, 999);
        f = g;

        std::cout << f.count(50) << "\n";

        auto it = f.begin();
        it++;
        it++;
        f.erase(it);

        g.Delete(50);
        g.Delete(77);
        g.Delete(2);
        g.Delete(85);

        auto it1 = f.begin();
        auto itf = f.Find(777);
        std::cout << (itf == f.end());

        std::cout << typeid(it).name();

        std::vector<Node<int>> a{ {567, 1}, {24, 2}, {3, 33}, {74, 35} };
        SkipList<int> m(a.begin(), a.end());

        f.Insert(a.begin(), a.end());
    }
    {
        multiSkipList<int> f;
        f.Insert(85ul, 66);
        f.Insert(50ul, 32);
        f.Insert(2ul, 97);
        f.Insert(50ul, 37);
    }
    return 0;
}