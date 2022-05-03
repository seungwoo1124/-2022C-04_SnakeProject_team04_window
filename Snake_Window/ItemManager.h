#pragma once
#include <vector>
using namespace std;

class Board;
class Snake;

struct Item
{
    Pos pos;
    ObjectType itemtype = ObjectType::ITEM_GROW;
};

class ItemManager
{
public:
    void Init(Board* board);

    void Update(uint64 deltaTick, int ch);

    void DropRandomItem(); 

    void RemoveItem(Pos pos); 

    Board* _board;
    Snake* _snake;
    vector<Item> _items;
    long sumTick = 0; 
};