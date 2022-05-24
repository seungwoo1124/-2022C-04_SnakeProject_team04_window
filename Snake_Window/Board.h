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

    const vector<vector<int>>& getBoard() { return _board; };

    int getTileType(Pos pos) { return _board[pos.y][pos.x]; };

    ItemManager* getItemmanager() { return _itemmanager; }
    GateManager* getGatemanager() { return _gatemanager; }

    void SetBoard(Pos pos, ObjectType type);

    void Render();

    bool isSnakeDead();

    int getRowSize() { return _rowSize; }
    int getColSize() { return _colSize; }
    bool isClear() { return _isClear; }
    int getLevel() { return _level; }
    void goNextLevel() { _level++; }

    const vector<int>& getScore() { return _score; }

    void PlusGrowScore() { _score[SCORE_GROW]++; }
    void PlusPoisonScore() { _score[SCORE_POISON]++; }
    void PlusGateScore() { _score[SCORE_GATE]++; }
    void UpdateSnakeLength();

    void CreateLevel1();
    void CreateLevel2();
    void CreateLevel3();
    void CreateLevel4();

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