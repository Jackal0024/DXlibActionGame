#pragma once

#include"../../World/IWorld.h"
#include<vector>
#include"../../Actor/Magic/Base/MagicList.h"

class MagicMenu
{
public:
	MagicMenu();
	MagicMenu(IWorld* world);
	void Update(float deltaTime);
	void Draw() const;
	~MagicMenu();
private:
	void PauseEnd();
	void CreateMagicText();
private:
	IWorld* mWorld;
	std::vector<int> mTextTexture;
	std::vector<MagicList> mList;
	MagicList mCurrentMagic;
	int mUnknownTexture;
	int mEquipmentTexture;
	int mIndex;
	bool mMagichas;
};
