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
    // 0.5 �ʰ� ������ ������ũ �̵� --> _direction �������� (_direction�� �Ӹ������ �ݴ�� �̵��� ����) --> GoNext()
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
    
    // ���� ��ġ�� snake�� ù��°
    Pos currentpos = _snake[0];
    Pos nextpos = currentpos + dp[_direction];
    int nexttile = _board->getBoardPos(nextpos);

    // ������ �ٲ�� �� Ÿ�ӿ� ������ũ �� ĭ�� ���� ��ȯ�� �̷������ ��
    // �ٷ� �� ĭ�� ������ ��������, snake head�� ������ ����Ű �Է����� �����ϸ� �� �� ���� <-- ���?
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
    // Ű���� �Է´�� _direction ����
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
    // ���� ���� ����
    return _direction;
}

void Snake::Grow()
{
    // _snakesize 1 ����
    _snakesize++;

    // tail ���⿡�� 1 ����(������ �¿��̸� x�� ��ȭ, ������ �����̸� y�� ��ȭ) _snake.push_back({ 1,0 });
    // 1, 0�� ���� ����
    if (_direction == DIR_UP) { // ��
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_DOWN) { // �Ʒ�
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_LEFT) { // ��
        _snake.push_back({ 1,0 });
    }
    else if (_direction == DIR_RIGHT) { // ��
        _snake.push_back({ 1,0 });
    }
}

void Snake::Shrink()
{
    // _snakesize 1 ����
    _snakesize--;

    // tail���⿡�� 1 ����
    _snake.pop_back();
}
