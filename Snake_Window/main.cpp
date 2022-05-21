#include "pch.h"
#include "Board.h"
#include "GameSceneManager.h"

Board board = Board();
GameSceneManager scene = GameSceneManager(&board);

int main()
{
    srand((unsigned int)time(NULL));
    initscr();
    noecho(); // don't show input 
    curs_set(false); // don't show cursors
    keypad(stdscr, true); // can input by keyboard
    nodelay(stdscr, true); // no wait input

    board.Init();

    scene.StartGameScene();
    
    uint64 prevTick = ::GetTickCount64();
    while (true)
    {
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - prevTick;
        prevTick = currentTick;
        int ch = getch();
        if (ch == 'q') break;

        if (ch == 'd') board.SetSnakeDie();

        board.Update(deltaTick, ch);

        if (board.isSnakeDead())
        {
            if (scene.RestartGameScene())
            {
                prevTick = GetTickCount64();
                continue;
            }
            else
            {
                clear();
                mvprintw(0, 0, "Game over");
                mvprintw(1, 0, "Your Score : ");
                refresh();
                Sleep(CLOCKS_PER_SEC * 3);
                break;
            }
        }
        if (board.isClear() == false)
            scene.Render();
    }
    endwin();
}