#pragma once

class Board;

class GateManager
{
public:
	void Init(Board* board);
	
	void Update(uint64 deltaTick);

	void CreateGate();

	vector<Pos> getGate() { return _gate; } // testcode

	bool isGate() { return _isgateCreate; }

	Pos getExit(Pos entrance);

private:
	Board* _board = nullptr;
	uint64 _sumTick = 0;
	bool _isgateCreate = false;
	vector<Pos> _gate;
};

