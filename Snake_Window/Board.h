#pragma once
#include <vector>
using namespace std;

class ItemManager;
class Snake;

class Board
{
public:
    void Init();

    void Update(uint64 deltaTick, int ch);

    void Render();

    ItemManager* _itemmanager;
    Snake* _snake;
    vector<vector<int> > _board;
    int _size;
    uint64 _fps = 0;
    uint64 _sumTick = 0;
    uint64 _sumframe = 0;
    bool _quit = false;
};