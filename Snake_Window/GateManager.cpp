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
	const vector<vector<int>>& board = _board->getBoard();
	vector<Pos> walllist;
	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board[0].size(); x++)
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
	Pos dp[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	int curDir = dir;
	int x = exit.x;
	int y = exit.y;
	int rowSize = _board->getRowSize();
	int colSize = _board->getColSize();

	if (y == 0)
		curDir = DIR_DOWN;
	else if (y == rowSize - 1)
		curDir = DIR_UP;
	else if (x == 0)
		curDir = DIR_RIGHT;
	else if (x == colSize - 1)
		curDir = DIR_LEFT;
	else // not side
	{
		int nexttile = _board->getTileType(exit + dp[curDir]);
		while (nexttile == (int)ObjectType::WALL)
		{
			curDir = (curDir + 1) % DIR_COUNT;
		}
	}

	return curDir;
}
