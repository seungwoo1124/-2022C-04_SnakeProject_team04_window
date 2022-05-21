#pragma once
#include <vector>
using namespace std;

class ItemManager;
class Snake;
class GateManager;

class Board
{
public:
    Board(int size = 21);
    virtual ~Board();

    void Init();

    void Update(uint64 deltaTick, int ch);

    vector<vector<int>> getBoard() { return _board; };

    int getBoardPos(Pos pos) { return _board[pos.y][pos.x]; };

    ItemManager* getItemmanager() { return _itemmanager; }
    GateManager* getGatemanager() { return _gatemanager; }

    void CreateLevel1();

    void SetBoard(Pos pos, ObjectType type);

    void Render();

    bool isSnakeDead();

    void SetSnakeDie(); // testcode

    int getRowSize() { return _rowSize; }
    int getColSize() { return _colSize; }
    bool isClear() { return _isClear; }

    const vector<int>& getScore() { return _score; }

private:
    ItemManager* _itemmanager = nullptr;
    GateManager* _gatemanager = nullptr;
    Snake* _snake = nullptr;
    vector<vector<int> > _board;
    int _rowSize;
    int _colSize;
    uint64 _fps = 0;
    uint64 _sumTick = 0;
    uint64 _sumframe = 0;
    bool _quit = false;
    int _level = 1;

    vector<int> _score;
    bool _isClear = false;
};