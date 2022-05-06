#include "pch.h"
#include "Snake.h"
#include "Board.h"

void Snake::Init(Board* board)
{
    _isDead = false;
    _sumTick = 0;
    _direction = DIR_RIGHT;
    _snakesize = 3;
    _snake = vector<Pos>(3, { 1, 0 });

    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = { 1, _snakesize - 1 - i };
    }
}

void Snake::Update(uint64 deltaTick, int ch)
{

}

bool Snake::IsCollision()
{
    return false;
}

void Snake::GoNext()
{
    
}

void Snake::SetDirection()
{

}

int Snake::Getdirection()
{
    return 0;
}