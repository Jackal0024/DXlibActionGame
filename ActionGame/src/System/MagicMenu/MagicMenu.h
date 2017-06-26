/*
*�}�W�b�N�̃��j���[�N���X
*�T�v�F�Q�[�����}�W�b�N��I�����鎞�̃V�X�e��
*/
#pragma once

#include"../../World/IWorld.h"
#include<vector>
#include"../../Actor/Magic/Base/MagicList.h"

class MagicMenu
{
private:
	enum Stick
	{
		UP,
		DOWN
	};
public:
	MagicMenu();
	MagicMenu(IWorld* world);
	void Update(float deltaTime);
	void Draw() const;
	~MagicMenu();
private:
	void PauseEnd();
	void CreateMagicText();
	bool StickCheck(Stick dir);
private:
	IWorld* mWorld;
	std::vector<int> mTextTexture;
	std::vector<MagicList> mList;
	MagicList mCurrentMagic;
	int mUnknownTexture;
	int mHelpTexture;
	int mEquipmentTexture;
	int mCursorRight;
	int mCursorLeft;
	int mIndex;
	bool mMagichas;
	int mStickX;
};
