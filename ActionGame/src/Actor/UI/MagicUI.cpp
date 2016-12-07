#include "MagicUI.h"
#include"../Player/Player.h"

MagicUI::MagicUI(IWorld * world, Vector3 position):
Actor(world, "HP", position, Capsule(Vector3(0, 0, 0), 0)),
mCurrentMagic(MagicList::FIREBALL)
{
	mFrameHandle = LoadGraph("./res/Texture/UI/MagicFrame.png");

	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/FireBallIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/IceNeedleIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/HealingIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/RockIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/FireWallIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/MineIcon.png"));
	mIconHandles.push_back(LoadGraph("./res/Texture/UI/MagicIcon/TrapIcon.png"));
}

MagicUI::~MagicUI()
{
	DeleteGraph(mFrameHandle);
	for (auto handle : mIconHandles)
	{
		DeleteGraph(handle);
	}
	mIconHandles.clear();
}

void MagicUI::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mCurrentMagic = ((Player*)player)->GetCurrentMagic();
}

void MagicUI::onDraw() const
{
	DrawGraph(mPosition.x, mPosition.y, mFrameHandle, TRUE);
	if (mCurrentMagic != MagicList::NONE)
	{
		int icon = mIconHandles[(int)mCurrentMagic];
		DrawGraph(mPosition.x, mPosition.y, icon, TRUE);
	}
}
