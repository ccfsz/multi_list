#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

#include "boost/container/small_vector.hpp"

using namespace std;

enum HookName
{
    Raw = 0,
    NumOfHooks = 1
};

struct Hook
{
    int prev;
    int next;
};

template <typename T>
struct Item
{
    T content;

    std::array<Hook, NumOfHooks> hooks;
};

template <typename Config>
class Container
{
    using ItemType = Item<typename Config::ContentTrait>;
    using LocType = uint16_t;

    boost::container::small_vector<ItemType, Config::InitialBufferSize> buffer;

    std::array<LocType, 10> heads;

    std::unordered_map<typename Config::OrderIdType, LocType> uolut;

public:
    void onDelete();
    void onInsert();
    void onTaken();
    void onAdjust();
    void print()
    {
        std::cout<<buffer.size()<<std::endl;
        for (auto &x : buffer)
        {
            std::cout <<" -> " << x.content;
        }
        std::cout << std::endl;
    }
};

struct BasicCarConfig
{
    static constexpr int InitialBufferSize = 500;
    using ContentTrait = int64_t;
};

struct LandRoverCofig:BasicCarConfig
{
    using OrderIdType = int64_t;
};

struct MercedesCofig:BasicCarConfig
{
    using OrderIdType = std::string;
};

struct RenaultCofig:BasicCarConfig
{
    using OrderIdType = int32_t;
};

int main()
{
    Container<LandRoverCofig> container;
    container.print();
}