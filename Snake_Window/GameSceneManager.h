#pragma once

class Board;

class GameSceneManager
{
public:
	bool RestartGameScene(Board* board);

	void StartGameScene();

private:
	Board* _board;
};

