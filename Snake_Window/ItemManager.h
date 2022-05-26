#pragma once
#include <vector>
using namespace std;

class Board;
class Snake;

struct Item
{
    Pos pos;
    uint64 dropTime = 0;
    ObjectType itemtype = ObjectType::ITEM_GROW;
};

class ItemManager
{
public:
    void Init(Board* board);

    void Update(uint64 deltaTick, int ch);

    void DropRandomItem(uint64 dropTime);

    void RemoveItem(Pos pos); 

    void RemoveFirstItem();

    vector<Item> _items;
private:
    Board* _board = nullptr;
    Snake* _snake = nullptr;
    uint64 _lastDropTime = 0;
    uint64 _sumTick = 0;
};