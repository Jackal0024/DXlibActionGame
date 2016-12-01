#include "PlayerSave.h"
#include"../../Actor/Magic/Base/MagicList.h"

PlayerSave & PlayerSave::getInstance()
{
	static PlayerSave data;
	return data;
}

void PlayerSave::Save(PlayerStatus player)
{
	mState = player;
}

PlayerStatus PlayerSave::Load()
{
	return mState;
}


void PlayerSave::Clear()
{
}

void PlayerSave::PlayerInit()
{
	PlayerStatus player;
	std::vector<MagicList> list;
	list.push_back(MagicList::FIREBALL);

	player.HP = 100;
	player.MaxHP = 100;
	player.MP = 100;
	player.MaxMP = 100;
	player.List = list;
	player.AtkBoost = 20;
	player.CurrentMagic = MagicList::FIREBALL;
	PlayerSave::getInstance().Save(player);
}

PlayerSave::PlayerSave():
	mState({100,100,100,100})
{
}
