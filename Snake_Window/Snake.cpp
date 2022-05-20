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
    _snake = vector<Pos>(3, { 1, 0 });

    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = { 1, _snakesize - 1 - i };
    }
}

void Snake::Update(uint64 deltaTick, int ch)
{
    // 0.5 초가 지나면 스네이크 이동 --> _direction 방향으로 (_direction이 머리방향과 반대로 이동시 실패) --> GoNext()
    _sumTick += deltaTick;
    if (_sumTick - _lastSumTick > 0.5 * CLOCKS_PER_SEC) {
        _lastSumTick = _sumTick;
        SetDirection(ch);
        GoNext();
    }
}

// if nextpos != Empty --> YES!!!!!!!!!
bool Snake::IsCollision(Pos nextpos)
{
    if (nextpos.x != NULL && nextpos.y != NULL)
        return true;
    return false;
}

// nextpos = currentpos + dp[direction]
void Snake::GoNext()
{
    // dp[direction] 이 무엇인가
    // 방향이 바뀌면 한 타임에 스네이크 한 칸씩 방향 전환이 이루어져야 함
    // 바로 앞 칸의 방향을 가져오고, snake head의 방향은 방향키 입력으로 설정하면 될 것 같음 <-- 어떻게?
    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = { 1, 0 }; // 1, 0은 변경 예정
    }
}

void Snake::SetDirection(int ch)
{
    if ((_direction == 0 && ch == 1) || (_direction == 1 && ch == 0) || (_direction == 2 && ch == 3) || (_direction == 3 && ch == 2)) {
        SetDie();
    }
    // 키보드 입력대로 _direction 설정
    else {
        _direction = ch;
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
