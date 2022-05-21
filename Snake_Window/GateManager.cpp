#include "pch.h"
#include "GateManager.h"
#include "Board.h"

void GateManager::Init(Board* board)
{
	_board = board;
	_sumTick = 0;
	_gate.clear();
	_isgateCreate = false;
}

void GateManager::Update(uint64 deltaTick)
{
	_sumTick += deltaTick;
	if (_isgateCreate == false && _sumTick > 10 * CLOCKS_PER_SEC)
		CreateGate();
	if (_isgateCreate)
	{
		_board->SetBoard(_gate[0], ObjectType::GATE);
		_board->SetBoard(_gate[1], ObjectType::GATE);
	}
}

void GateManager::CreateGate()
{
	vector<vector<int>> board = _board->getBoard();
	vector<Pos> walllist;
	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board.size(); x++)
		{
			if (board[y][x] == (int)ObjectType::WALL)
			{
				Pos wallpos = Pos{ y, x };
				walllist.push_back(wallpos);
			}
		}
	}
	int gateidx = rand() % walllist.size();
	_gate.push_back(walllist[gateidx]);
	
	walllist.erase(walllist.begin() + gateidx, walllist.begin() + gateidx + 1);
	gateidx = rand() % walllist.size();
	_gate.push_back(walllist[gateidx]);

	_isgateCreate = true;
}

Pos GateManager::getExit(Pos entrance)
{
	Pos exitgate = _gate[0];
	if (_gate[0] == entrance)
		exitgate = _gate[1];
	return exitgate;
}

int GateManager::getExitDir(Pos exit, int dir)
{
	int ret = dir;
	int x = exit.x;
	int y = exit.y;
	int boardSize = _board->getRowSize();

	if (y == 0)
		ret = DIR_DOWN;
	else if (y == boardSize - 1)
		ret = DIR_UP;
	else if (x == 0)
		ret = DIR_RIGHT;
	else if (x == boardSize - 1)
		ret = DIR_LEFT;

	return ret;
}
