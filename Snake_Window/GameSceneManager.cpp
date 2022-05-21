#include "pch.h"
#include "GameSceneManager.h"
#include "Board.h"

GameSceneManager::GameSceneManager(Board* board)
{
	_board = board;
}

bool GameSceneManager::RestartGameScene()
{
	nodelay(stdscr, false);
	clear();
	mvprintw(10, 0, "press 'r' button to restart and others finish game");
	refresh();
	int re = getch();
	if (re == 'r')
	{
		_board->Init();
		nodelay(stdscr, true);
		clear();
		StartGameScene();
		return true;
	}
	return false;
}

void GameSceneManager::StartGameScene()
{
	mvprintw(10, 0, "Game Start after 3 second");
	refresh();
	Sleep(CLOCKS_PER_SEC);

	clear();
	mvprintw(10, 0, "Game Start after 2 second");
	refresh();
	Sleep(CLOCKS_PER_SEC);

	clear();
	mvprintw(10, 0, "Game Start after 1 second");
	refresh();
	Sleep(CLOCKS_PER_SEC);
}

void GameSceneManager::Render()
{
	clear();
	_board->Render();
	RenderScore();
	refresh();
}

void GameSceneManager::RenderScore()
{
	const vector<int> score = _board->getScore();
	int colSize = _board->getColSize();
	int rowSize = _board->getRowSize();

	char len = (score[SCORE_LENGTH] >= 10) ? 'v' : ' ';
	char grow = (score[SCORE_GROW] >= 5) ? 'v' : ' ';
	char poison = (score[SCORE_POISON] >= 2) ? 'v' : ' ';
	char gate = (score[SCORE_GATE] >= 1) ? 'v' : ' ';

	mvprintw(0, colSize + 1, "B : 10 (%c)", len);
	mvprintw(1, colSize + 1, "+ : 5 (%c)", grow);
	mvprintw(2, colSize + 1, "- : 2 (%c)", poison);
	mvprintw(3, colSize + 1, "G : 1 (%c)", gate);
}
