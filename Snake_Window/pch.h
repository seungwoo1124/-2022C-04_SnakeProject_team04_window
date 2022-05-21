#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <curses.h>

using namespace std;

struct Pos
{
    bool operator==(Pos& other)
    {
        return y == other.y && x == other.x;
    }

    bool operator!=(Pos& other)
    {
        return !(*this == other);
    }

    Pos operator+(Pos& other)
    {
        Pos ret = {0, 0};
        ret.y = y + other.y;
        ret.x = x + other.x;
        return ret;
    }

    Pos& operator+=(Pos& other)
    {
        y += other.y;
        x += other.x;
        return *this;
    }

    int y;
    int x;
};

enum Dir
{
    DIR_UP = 0,
    DIR_DOWN = 1,
    DIR_LEFT = 2,
    DIR_RIGHT = 3,

    DIR_COUNT = 4
};

enum Score
{
    SCORE_LENGTH = 0,
    SCORE_GROW = 1,
    SCORE_POISON = 2,
    SCORE_GATE = 3,
};

enum class ObjectType
{
    EMPTY = 0,
    WALL = 1,
    IMMUNE_WALL = 2,

    SNAKE_HEAD = 3,
    SNAKE_BODY = 4,

    ITEM_GROW = 5,
    ITEM_POISON = 6,

    GATE = 7,
};

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;