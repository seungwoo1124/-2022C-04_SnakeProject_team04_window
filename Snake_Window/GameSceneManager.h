#pragma once

class Board;

class GameSceneManager
{
public:
	GameSceneManager(Board* board);
	bool RestartGameScene();

	void StartGameScene();

	void Render();
	void RenderScore();

private:
	Board* _board;
};

