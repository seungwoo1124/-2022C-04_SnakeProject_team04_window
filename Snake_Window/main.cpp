#include "pch.h"
#include "Board.h"
#include "GameSceneManager.h"

#define HEAD  1 
#define BODY  2 
#define GROW   3 
#define POISON  4
#define DOOR  5 
#define WAL  6 
#define IMMUNEWAL 7

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
    start_color();
    init_pair(HEAD, COLOR_CYAN, COLOR_CYAN); 
    init_pair(BODY, COLOR_WHITE, COLOR_YELLOW); 
    init_pair(GROW, COLOR_WHITE, COLOR_GREEN); 
    init_pair(POISON, COLOR_WHITE, COLOR_RED); 
    init_pair(DOOR, COLOR_MAGENTA, COLOR_MAGENTA); 
    init_pair(WAL, COLOR_WHITE, COLOR_WHITE);
    init_pair(IMMUNEWAL, COLOR_BLACK, COLOR_BLACK);


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
        else
        {
            if (board.getLevel() == 4)
            {
                scene.GameClearScene();
                break;
            }
            scene.LevelClearScene();
        }
    }
    endwin();
}