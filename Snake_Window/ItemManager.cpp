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

void ItemManager::Update(uint64 deltaTick, int ch)
{
}

void ItemManager::DropRandomItem()
{
}

void ItemManager::RemoveItem(Pos pos)
{
}
