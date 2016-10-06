#pragma once

#include"../../World/IWorld.h"

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
private:
	IWorld* mWorld;
	int mFadeTexture;
};
