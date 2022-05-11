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

void GateManager::getExit(Pos entrance)
{

}