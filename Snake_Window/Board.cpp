#include "pch.h"
#include "Board.h"
#include "ItemManager.h"
#include "Snake.h"

void Board::Init()
{
    _size = 21;
    _board = vector<vector<int>>(_size, vector<int>(_size, 0));
    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            if (y == 0 || x == 0 || y == _size - 1 || x == _size - 1)
                _board[y][x] = 1;
        }
    }
    _board[0][0] = 2;
    _board[0][_size - 1] = 2;
    _board[_size - 1][0] = 2;
    _board[_size - 1][_size - 1] = 2;

    _itemmanager->Init(this);
    _snake->Init(this);
}

void Board::Update(uint64 deltaTick, int ch)
{
    _itemmanager->Update(deltaTick, ch);
    _snake->Update(deltaTick, ch);

    _sumTick += deltaTick;
    _sumframe++;
    if (_sumTick >= CLOCKS_PER_SEC)
    {
        _sumTick = 0;
        _fps = _sumframe;
        _sumframe = 0;
    }
}

void Board::Render()
{
    clear();
    for (int y = 0; y < _size; y++)
    {
        for (int x = 0; x < _size; x++)
        {
            int tile = _board[y][x];
            switch (tile)
            {
            case (int)ObjectType::EMPTY:
                mvprintw(y, x, " ");
                break;
            case (int)ObjectType::WALL:
                mvprintw(y, x, "W");
                break;
            case (int) ObjectType::IMMUNE_WALL:
                mvprintw(y, x, "I");
                break;
            }
        }
    }
    mvprintw(_size, 0, "fps : %d", _fps);
    refresh();
}