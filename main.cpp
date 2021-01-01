#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

#include "boost/container/small_vector.hpp"

using namespace std;
constexpr int NumOfHooks = 10;

enum HookName
{
    Raw=0,
};

struct Hook
{
    int prev;
    int next;
};

template <typename T>
class Item
{
    T content;

    std::array<Hook, 10> hooks;
};

template <typename Config>
class Container
{
    using ItemType = Item<typename Config::ContentTrait>;
    using LocType = uint16_t;

    boost::container::small_vector<ItemType, 100> buffer;

    std::array<LocType, 10> heads;

    std::unordered_map<typename Config::OrderIdType, LocType> uolut;

public:
    void onDelete();
    void onInsert();
    void onTaken();
    void onAdjust();
};

int main()
{
    vector<string> msg{"Hello", "C++", "World"};

    for (const string &word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}