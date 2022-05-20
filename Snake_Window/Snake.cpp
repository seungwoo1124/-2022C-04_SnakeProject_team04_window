#include "pch.h"
#include "Snake.h"
#include "Board.h"
#include "ItemManager.h"
#include "GateManager.h"

// seojeong

void Snake::Init(Board* board)
{
    _board = board;
    _itemManager = board->getItemmanager();
    _gateManager = board->getGatemanager();

    _isDead = false;
    _sumTick = 0;
    _lastSumTick = 0;
    _direction = DIR_RIGHT;
    _snakesize = 3;
    _snake = { { 1, 3 }, { 1, 2 }, { 1, 1 } };

    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = { 1, _snakesize - 1 - i };
    }
}

void Snake::Update(uint64 deltaTick, int ch)
{
    SetDirection(ch);
    // 0.5 초가 지나면 스네이크 이동 --> _direction 방향으로 (_direction이 머리방향과 반대로 이동시 실패) --> GoNext()
    _sumTick += deltaTick;
    if (_sumTick - _lastSumTick > 0.5 * CLOCKS_PER_SEC) {
        _lastSumTick = _sumTick;
        GoNext();
    }
}

// if nextpos != Empty --> YES!!!!!!!!!
bool Snake::IsCollision(Pos nextpos)
{
    int tile = _board->getBoardPos(nextpos);
    if (tile != (int)ObjectType::EMPTY)
        return true;
    return false;
}

// nextpos = currentpos + dp[direction]
void Snake::GoNext()
{
    Pos dp[4] = { Pos{-1,0}, Pos{1,0}, Pos{0,-1}, Pos{0,1} };
    
    // 현재 위치는 snake의 첫번째
    Pos currentpos = _snake[0];
    Pos nextpos = currentpos + dp[_direction];
    int nexttile = _board->getBoardPos(nextpos);

    // 방향이 바뀌면 한 타임에 스네이크 한 칸씩 방향 전환이 이루어져야 함
    // 바로 앞 칸의 방향을 가져오고, snake head의 방향은 방향키 입력으로 설정하면 될 것 같음 <-- 어떻게?
    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = nextpos;
    }
}

void Snake::SetDirection(int ch)
{
    KEY_UP;
    if ((_direction == DIR_UP && ch == KEY_DOWN) || (_direction == DIR_DOWN && ch == KEY_UP) || 
        (_direction ==DIR_LEFT && ch == KEY_RIGHT) || (_direction == DIR_RIGHT && ch == KEY_LEFT)) {
        SetDie();
    }
    // 키보드 입력대로 _direction 설정
    else {
        switch (ch)
        {
        case(KEY_UP):
            _direction = DIR_UP;
            break;
        case(KEY_DOWN):
            _direction = DIR_DOWN;
            break;
        case(KEY_LEFT):
            _direction = DIR_LEFT;
            break;
        case(KEY_RIGHT):
            _direction = DIR_RIGHT;
            break;
        }
        
    }
}

int Snake::Getdirection()
{
    // 현재 방향 리턴
    return _direction;
}

void Snake::Grow()
{
    // _snakesize 1 증가
    _snakesize++;

    // tail 방향에서 1 증가(방향이 좌우이면 x값 변화, 방향이 상하이면 y값 변화) _snake.push_back({ 1,0 });
    // 1, 0은 변경 예정
    if (_direction == DIR_UP) { // 위
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_DOWN) { // 아래
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_LEFT) { // 왼
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_RIGHT) { // 오
        _snake.push_back({ 1,0 });
    }
}

void Snake::Shrink()
{
    // _snakesize 1 감소
    _snakesize--;

    // tail방향에서 1 감소
    _snake.pop_back();
}
