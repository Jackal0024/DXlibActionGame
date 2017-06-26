/*
*プレイヤーセーブクラス
*概要：プレイヤーのステータスを管理
*/
#pragma once

#include"../../Actor/Player/Player.h"

class PlayerSave
{
public:
	static PlayerSave& getInstance();
	void Save(PlayerStatus player);
	PlayerStatus Load();
	void Clear();
	void PlayerInit();

private:
	PlayerSave();

private:
	PlayerStatus mState;


};
