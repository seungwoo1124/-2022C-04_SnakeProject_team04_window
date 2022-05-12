#include "pch.h"
#include "Board.h"
#include "ItemManager.h"
#include "GateManager.h"
#include "Snake.h"

Board::Board()
{
    _itemmanager = new ItemManager();
    _snake = new Snake();
    _gatemanager = new GateManager();
    _size = 21;
    _fps = 0;
    _sumTick = 0;
    _sumframe = 0;
    _quit = false;
}

Board::Board(int size)
{
    _itemmanager = new ItemManager();
    _snake = new Snake();
    _size = size;
    _fps = 0;
    _sumTick = 0;
    _sumframe = 0;
    _quit = false;
}

Board::~Board()
{
    delete _itemmanager;
    delete _snake;
    delete _gatemanager;
}

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
    _gatemanager->Init(this);
}

void Board::Update(uint64 deltaTick, int ch)
{
    _itemmanager->Update(deltaTick, ch);
    _snake->Update(deltaTick, ch);
    _gatemanager->Update(deltaTick);

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
    vector<Pos> gate = _gatemanager->getGate();
    if (_gatemanager->isGate())
    {
        mvprintw(_size + 1, 0, "gate1 y : %d, x : %d", gate[0].y, gate[1].x);
        mvprintw(_size + 2, 0, "gate2 y : %d, x : %d", gate[1].y, gate[1].x);
    }
    refresh();
}

bool Board::isSnakeDead()
{
    return _snake->IsDead();
}

void Board::SetSnakeDie() // testcode
{
    _snake->SetDie();
}
