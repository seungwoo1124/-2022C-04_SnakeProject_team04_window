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

    //3초가 지난후 item 떨굼. 이때 board에 생성되는 최대 item은 3개 
    if (_sumTick -_lastDropTime > 3 * CLOCKS_PER_SEC && _items.size()<3 ) 
    {   
        _lastDropTime = _sumTick;
        DropRandomItem(_lastDropTime);
    }

    // 5초가 지난 item 삭제
    for (int i = 0; i < _items.size(); i++) 
    {
        if (_sumTick - _items[i].dropTime > 5 * CLOCKS_PER_SEC)  
        {
            _board->SetBoard(_items[i].pos, ObjectType::EMPTY);
            RemoveItem(_items[i].pos);
        }
    }

    //test
    
     //board에 갱신
    for (int i = 0; i < _items.size(); i++) { _board->SetBoard(_items[i].pos, _items[i].itemtype);  }

}

void ItemManager::DropRandomItem(long dropTime) // add Item to vector _items
{   
    Item item;
    vector<vector<int>> board = _board->getBoard();
    vector<Pos> snakePos;

    int randNum = rand() % 2; //grow또는 poison이 50%의 확률로 _items에 삽입되도록.
    item.pos.x = (rand() % (board.size() - 2)) + 1;
    item.pos.y = (rand() % (board.size() - 2)) + 1;

    // item이 snake의 몸통 혹은 머리에 떨어지는지 확인. 
    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board.size(); x++)
        {
            if (board[y][x] == (int)ObjectType::SNAKE_HEAD || board[y][x] == (int)ObjectType::SNAKE_BODY)
            {
                Pos pos;
                pos.y = y;
                pos.x = x;
                snakePos.push_back(pos);
            }
        }
    }

    for (int i = 0; i < snakePos.size(); i++) { 
        if (item.pos == snakePos[i]) { 
            DropRandomItem(dropTime); 
        }
    }
    
    //_items에 추가하기
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

