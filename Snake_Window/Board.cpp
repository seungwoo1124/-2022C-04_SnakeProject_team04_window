#include "pch.h"
#include "Board.h"
#include "ItemManager.h"
#include "GateManager.h"
#include "Snake.h"


Board::Board(int size)
{
    _itemmanager = new ItemManager();
    _snake = new Snake();
    _gatemanager = new GateManager();
    _rowSize = size;
    _colSize = size;
    _fps = 0;
    _sumTick = 0;
    _sumframe = 0;
    _quit = false;
    _score = vector<int>(4, 0);
    _level = 1;
    _isClear = false;
}

Board::~Board()
{
    delete _itemmanager;
    delete _snake;
    delete _gatemanager;
}

void Board::Init()
{
    switch (_level)
    {
    case (1):
        CreateLevel1();
        break;
    case (2):
        CreateLevel2();
        _snake->SetInterval(0.1375);
        break;
    case (3):
        CreateLevel3();
        _snake->SetInterval(0.1375);
        break;
    case(4):
        CreateLevel4();
        _snake->SetInterval(0.1375);
        break;
    }
    _itemmanager->Init(this);
    _gatemanager->Init(this);
    _snake->Init(this);
    _score = vector<int>(4, 0);
    _isClear = false;
}

void Board::Update(uint64 deltaTick, int ch)
{
    _itemmanager->Update(deltaTick, ch);
    _gatemanager->Update(deltaTick);
    _snake->Update(deltaTick, ch);

    _sumTick += deltaTick;
    _sumframe++;
    if (_sumTick >= CLOCKS_PER_SEC)
    {
        _sumTick = 0;
        _fps = _sumframe;
        _sumframe = 0;
    }

    if (_score[SCORE_LENGTH] >= 10 && _score[SCORE_GROW] >= 5 &&
        _score[SCORE_POISON] >= 2 && _score[SCORE_GATE] >= 1)
        _isClear = true;
}

void Board::SetBoard(Pos pos, ObjectType type)
{
    _board[pos.y][pos.x] = (int)type;
}

void Board::Render()
{
    for (int y = 0; y < _rowSize; y++)
    {
        for (int x = 0; x < _colSize; x++)
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
            case (int)ObjectType::IMMUNE_WALL:
                mvprintw(y, x, "I");
                break;

            case (int)ObjectType::SNAKE_BODY:
                mvprintw(y, x, "S");
                break;
            case (int)ObjectType::SNAKE_HEAD:
                mvprintw(y, x, "H");
                break;

            case (int)ObjectType::ITEM_GROW:
                mvprintw(y, x, "G");
                break;
            case (int)ObjectType::ITEM_POISON:
                mvprintw(y, x, "P");
                break;
            case (int)ObjectType::GATE:
                mvprintw(y, x, "D"); // door
                break;
            }
        }
    }
    mvprintw(_rowSize, 0, "fps : %d", _fps);
    vector<Pos> gate = _gatemanager->getGate();
    // gate 위치 출력
    if (_gatemanager->isGate())
    {
        mvprintw(_rowSize + 1, 0, "gate1 y : %d, x : %d", gate[0].y, gate[1].x);
        mvprintw(_rowSize + 2, 0, "gate2 y : %d, x : %d", gate[1].y, gate[1].x);
    }
}

bool Board::isSnakeDead()
{
    return _snake->IsDead();
}

void Board::UpdateSnakeLength()
{
    int snakeSize = _snake->GetSnakeSize();
    _score[SCORE_LENGTH] = snakeSize;
    if (snakeSize < 3)
        _snake->SetDie();
}

void Board::CreateLevel1()
{
    _colSize = _rowSize;
    _board = vector<vector<int>>(_rowSize, vector<int>(_colSize, 0));
    for (int y = 0; y < _rowSize; y++)
    {
        for (int x = 0; x < _colSize; x++)
        {
            if (y == 0 || x == 0 || y == _rowSize - 1 || x == _colSize - 1)
                _board[y][x] = 1;
        }
    }
    _board[0][0] = 2;
    _board[0][_colSize - 1] = 2;
    _board[_rowSize - 1][0] = 2;
    _board[_rowSize - 1][_colSize - 1] = 2;
}
void Board::CreateLevel2()
{
    _colSize = 2 * _rowSize;
    _board = vector<vector<int>>(_rowSize, vector<int>(_colSize, 0));
    for (int y = 0; y < _rowSize; y++)
    {
        for (int x = 0; x < _colSize; x++)
        {
            if (y == 0 || x == 0 || y == _rowSize - 1 || x == _colSize - 1)
                _board[y][x] = 1;
        }
    }
    _board[0][0] = 2;
    _board[0][_colSize - 1] = 2;
    _board[_rowSize - 1][0] = 2;
    _board[_rowSize - 1][_colSize - 1] = 2;
}
void Board::CreateLevel3()
{
    _colSize = 2 * _rowSize;
    _board = vector<vector<int>>(_rowSize, vector<int>(_colSize, 0));
    for (int y = 0; y < _rowSize; y++)
    {
        for (int x = 0; x < _colSize; x++)
        {
            if (y == 0 || x == 0 || y == _rowSize - 1 || x == _colSize - 1)
                _board[y][x] = 1;
        }
    }
    _board[0][0] = 2;
    _board[0][_colSize - 1] = 2;
    _board[_rowSize - 1][0] = 2;
    _board[_rowSize - 1][_colSize - 1] = 2;

    for (int y = _rowSize * 1 / 4; y < _rowSize * 3 / 4; y++)
    {
        _board[y][_colSize/2] = 1;
    }
}
void Board::CreateLevel4()
{
    _colSize = 2 * _rowSize;
    _board = vector<vector<int>>(_rowSize, vector<int>(_colSize, 0));
    for (int y = 0; y < _rowSize; y++)
    {
        for (int x = 0; x < _colSize; x++)
        {
            if (y == 0 || x == 0 || y == _rowSize - 1 || x == _colSize - 1)
                _board[y][x] = 1;
        }
    }
    _board[0][0] = 2;
    _board[0][_colSize - 1] = 2;
    _board[_rowSize - 1][0] = 2;
    _board[_rowSize - 1][_colSize - 1] = 2;

    for (int y = _rowSize * 1 / 4; y < _rowSize * 3 / 4; y++)
    {
        for (int x = _colSize * 1 / 4; x < _colSize * 3 / 4; x++)
        {
            if (y == _rowSize / 2 && x == _colSize / 2)
                _board[y][x] = 2;
            else if (y == _rowSize / 2 || x == _colSize / 2)
                _board[y][x] = 1;
        }
    }
}

