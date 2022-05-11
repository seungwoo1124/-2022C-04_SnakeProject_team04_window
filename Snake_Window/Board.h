#pragma once
#include <vector>
using namespace std;

class ItemManager;
class Snake;
class GateManager;

class Board
{
public:
    Board();
    Board(int size);
    virtual ~Board();

    void Init();

    void Update(uint64 deltaTick, int ch);

    vector<vector<int>> getBoard() { return _board; };

    void Render();

    bool isSnakeDead();

    void SetSnakeDie(); // testcode

private:
    ItemManager* _itemmanager = nullptr;
    GateManager* _gatemanager = nullptr;
    Snake* _snake = nullptr;
    vector<vector<int> > _board;
    int _size;
    uint64 _fps = 0;
    uint64 _sumTick = 0;
    uint64 _sumframe = 0;
    bool _quit = false;
};