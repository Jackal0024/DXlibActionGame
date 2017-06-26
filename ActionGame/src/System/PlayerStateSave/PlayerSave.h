/*
*�v���C���[�Z�[�u�N���X
*�T�v�F�v���C���[�̃X�e�[�^�X���Ǘ�
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
