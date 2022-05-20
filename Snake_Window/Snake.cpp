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
    // 0.5 �ʰ� ������ ������ũ �̵� --> _direction �������� (_direction�� �Ӹ������ �ݴ�� �̵��� ����) --> GoNext()
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
    // dp[direction] �� �����ΰ�
    // ������ �ٲ�� �� Ÿ�ӿ� ������ũ �� ĭ�� ���� ��ȯ�� �̷������ ��
    // �ٷ� �� ĭ�� ������ ��������, snake head�� ������ ����Ű �Է����� �����ϸ� �� �� ���� <-- ���?
    for (int i = 0; i < _snakesize; i++)
    {
        _snake[i] = { 1, 0 }; // 1, 0�� ���� ����
    }
}

void Snake::SetDirection(int ch)
{
    if ((_direction == 0 && ch == 1) || (_direction == 1 && ch == 0) || (_direction == 2 && ch == 3) || (_direction == 3 && ch == 2)) {
        SetDie();
    }
    // Ű���� �Է´�� _direction ����
    else {
        _direction = ch;
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
