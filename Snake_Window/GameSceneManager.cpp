#include "pch.h"
#include "GameSceneManager.h"
#include "Board.h"

bool GameSceneManager::RestartGameScene(Board* board)
{
	nodelay(stdscr, false);
	clear();
	mvprintw(10, 0, "press 'r' button to restart and others finish game");
	refresh();
	int re = getch();
	if (re == 'r')
	{
		board->Init();
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
