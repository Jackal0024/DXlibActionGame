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

PlayerSave::PlayerSave():
	mState({100,100,100,100})
{
}
