#pragma once
#include "pch.h"
#include "ItemManager.h"
#include "Board.h"

void ItemManager::Init(Board* board)
{
	_board = board;
	_items.clear();
	_sumTick = 0;
}

// after 3second DropItem, if snake eat Item remove(pos), after 5second RemovefirstItem
void ItemManager::Update(uint64 deltaTick, int ch)
{
    _sumTick += deltaTick;

    //3�ʰ� ������ item ����. �̶� board�� �����Ǵ� �ִ� item�� 3�� 
    if (_sumTick -_lastDropTime > 3 * CLOCKS_PER_SEC && _items.size()<3 ) 
    {   
        _lastDropTime = _sumTick;
        DropRandomItem(_lastDropTime);
    }

    // 5�ʰ� ���� item ����
    if (_items.size() > 0)
    {
        if (_sumTick - _items[0].dropTime > 5 * CLOCKS_PER_SEC)
        {
            _board->SetBoard(_items[0].pos, ObjectType::EMPTY);
            RemoveFirstItem();
        }
    }
    
     //board�� ����
    for (int i = 0; i < _items.size(); i++) { _board->SetBoard(_items[i].pos, _items[i].itemtype);  }

}

void ItemManager::DropRandomItem(uint64 dropTime) // add Item to vector _items
{   
    Item item;
    vector<vector<int>> board = _board->getBoard();
    vector<Pos> notSnakePos;

    // item�� snake�� ���� Ȥ�� �Ӹ��� ���������� Ȯ��. 
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board.size(); x++)
        {
            if (board[y][x] == (int)ObjectType::EMPTY)
            {
                Pos pos;
                pos.y = y;
                pos.x = x;
                notSnakePos.push_back(pos);
            }
        }
    }
    //item.pos�� notSnakePos�� �ϳ� ��� 
    int randIndex = rand() % notSnakePos.size();
    item.pos = notSnakePos[randIndex];

    //_items�� �߰��ϱ�
    int randNum = rand() % 2; //grow�Ǵ� poison�� 50%�� Ȯ���� _items�� ���Եǵ���.

    if (randNum == 0) { 
        item.itemtype = ObjectType::ITEM_GROW;
        item.dropTime = dropTime;
        _items.push_back(item); }
    else { 
        item.itemtype = ObjectType::ITEM_POISON;
        item.dropTime = dropTime;
        _items.push_back(item);
    }

}

void ItemManager::RemoveItem(Pos pos) // remove Items in _items that same pos
{
    for (int i = 0; i < _items.size(); i++) {
        if (_items[i].pos == pos) { _items.erase(_items.begin()+i); }
    }
}

// be careful using this function.
void ItemManager::RemoveFirstItem()
{
	_items.erase(_items.begin());
}

