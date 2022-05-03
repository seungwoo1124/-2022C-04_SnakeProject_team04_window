#include "pch.h"
#include "Board.h"

Board board;

int main()
{
    srand((unsigned int)time(NULL));
    initscr();
    noecho(); // don't show input 
    curs_set(false); // don't show cursors
    keypad(stdscr, true); // can input by keyboard
    nodelay(stdscr, true); // no wait input

    board.Init();
    
    uint64 prevTick = ::GetTickCount64();
    while (true)
    {
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - prevTick;
        prevTick = currentTick;
        int ch = getch();
        if (ch == 'q') break;

        board.Update(deltaTick, ch);

        board.Render();
    }
    endwin();
}