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
	void ListUp();
	void CreateMagicText(MagicList magic);
private:
	IWorld* mWorld;
	int mFadeTexture;
	std::vector<int> mTextTexture;
	std::vector<MagicList> mList;
	int mIndex;
};
