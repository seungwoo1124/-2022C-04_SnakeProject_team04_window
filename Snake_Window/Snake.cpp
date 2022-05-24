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
    int startYpos = board->getRowSize() / 4;
    int startXpos = 1;
    _snake = vector<Pos>(3, { startYpos, startXpos });
}

void Snake::Update(uint64 deltaTick, int ch)
{
    SetDirection(ch);
    // 0.5 초가 지나면 스네이크 이동 --> _direction 방향으로 (_direction이 머리방향과 반대로 이동시 실패) --> GoNext()
    _sumTick += deltaTick;
    if (_sumTick - _lastSumTick > _interval * CLOCKS_PER_SEC) {
        _lastSumTick = _sumTick;
        GoNext();
        _board->UpdateSnakeLength();
    }
}

// if nextpos != Empty --> YES!!!!!!!!!
bool Snake::IsCollision(Pos nextpos)
{
    int tile = _board->getTileType(nextpos);
    if (tile != (int)ObjectType::EMPTY)
        return true;
    return false;
}

// nextpos = currentpos + dp[direction]
void Snake::GoNext()
{
    Pos dp[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
    
    // 현재 위치는 snake의 첫번째
    Pos currentpos = _snake[0];
    Pos nextpos = currentpos + dp[_direction];
    int nexttile = _board->getTileType(nextpos);

    // if gate
    
    if (nexttile == (int)ObjectType::GATE) {
        currentpos = _gateManager->getExit(nextpos);
        _direction = _gateManager->getExitDir(currentpos, _direction);
        nextpos = currentpos + dp[_direction];
        nexttile = _board->getTileType(nextpos);
        _board->PlusGateScore();
    }

    switch (nexttile)
    {
    case (int)ObjectType::WALL:
        SetDie();
        break;

    case (int)ObjectType::SNAKE_BODY:
        SetDie();
        break;

    case (int)ObjectType::ITEM_GROW:
        _itemManager->RemoveItem(nextpos);
        Grow();
        break;

    case (int)ObjectType::ITEM_POISON:
        _itemManager->RemoveItem(nextpos);
        Shrink();
        break;
    }

    Pos lastpos = _snake[_snakesize - 1];
    _board->SetBoard(lastpos, ObjectType::EMPTY);

    for (int i = _snakesize - 1; i > 0; i--) {
        _snake[i] = _snake[i - 1];
    }
    _snake[0] = nextpos;

    for (Pos snakePos : _snake)
    {
        _board->SetBoard(snakePos, ObjectType::SNAKE_BODY);
    }
    _board->SetBoard(_snake[0], ObjectType::SNAKE_HEAD);
}

void Snake::SetDirection(int ch)
{
    KEY_UP;
    if ((_direction == DIR_UP && ch == KEY_DOWN) || (_direction == DIR_DOWN && ch == KEY_UP) || 
        (_direction == DIR_LEFT && ch == KEY_RIGHT) || (_direction == DIR_RIGHT && ch == KEY_LEFT)) {
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
    Pos tail = _snake[_snakesize - 1];
    _snake.push_back(tail);
    _board->PlusGrowScore();

    // _snakesize 1 증가
    _snakesize++;
}

void Snake::Shrink()
{
    _board->PlusPoisonScore();
    // _snakesize 1 감소
    _snakesize--;

    // 남겨진 몸체 처리
    _board->SetBoard(_snake.back(), ObjectType::EMPTY);

    // tail방향에서 1 감소
    _snake.pop_back();
}
