#pragma once

#include"../../Actor/Player/Player.h"

class PlayerSave
{
public:
	static PlayerSave& getInstance();
	void Save(PlayerStatus player);
	PlayerStatus Load();
	void Clear();

private:
	PlayerSave();

private:
	PlayerStatus mState;


};
