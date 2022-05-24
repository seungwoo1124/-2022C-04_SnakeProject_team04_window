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

	void LevelClearScene();
	void GameClearScene();

private:
	Board* _board;
};

