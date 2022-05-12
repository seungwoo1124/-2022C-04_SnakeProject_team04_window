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
}

void ItemManager::DropRandomItem() // add Item to vector _items
{
}

void ItemManager::RemoveItem(Pos pos) // remove Items in _items that same pos
{
}

// be careful using this function.
void ItemManager::RemoveFirstItem()
{
	_items.erase(_items.begin());
}
