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

    vector<Pos> _snake;
    Board* _board;
    ItemManger* _itemManager;
    int _snakesize;
    long sumTick = 0;
    bool _isDead = false;
    int _direction = DIR_RIGHT;
};