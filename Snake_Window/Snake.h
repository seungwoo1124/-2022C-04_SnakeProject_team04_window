#pragma once

class Board;
class ItemManager;
class GateManager;

class Snake
{
public:
    void Init(Board* board);

    void Update(uint64 deltaTick, int ch);

    bool IsCollision(Pos nextpos);

    bool IsDead() {return _isDead;}

    void GoNext();

    void SetDirection(int ch);

    int Getdirection();

    int GetSnakeSize() { return _snakesize; }

    void SetDie() { _isDead = true; } // test code

    void Grow();

    void Shrink();

private:
    vector<Pos> _snake;
    Board* _board = nullptr;
    ItemManager* _itemManager = nullptr;
    GateManager* _gateManager = nullptr;
    int _snakesize;
    long _sumTick = 0;
    long _lastSumTick = 0;
    bool _isDead = false;
    int _direction = DIR_RIGHT;
};