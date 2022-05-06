#pragma once

class Board;
class ItemManger;

class Snake
{
public:
    void Init(Board* board);

    void Update(uint64 deltaTick, int ch);

    bool IsCollision();

    bool IsDead() {return _isDead;}

    void GoNext();

    void SetDirection();

    int Getdirection();

    int GetSnakeSize() { return _snakesize; }

    void SetDie() { _isDead = true; } // test code

private:
    vector<Pos> _snake;
    Board* _board = nullptr;
    ItemManger* _itemManager = nullptr;
    int _snakesize;
    long _sumTick = 0;
    bool _isDead = false;
    int _direction = DIR_RIGHT;
};