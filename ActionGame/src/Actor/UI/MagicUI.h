#pragma once

#include"../Base/Actor.h"
#include"../Magic/Base/MagicList.h"
#include<vector>

class MagicUI :public  Actor
{
public:
	MagicUI(IWorld* world, Vector3 position);
	~MagicUI();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	int mFrameHandle;
	MagicList mCurrentMagic;
	std::vector<int> mIconHandles;
	
	
};