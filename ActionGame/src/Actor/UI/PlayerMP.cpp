#include "PlayerMP.h"
#include"../Player/Player.h"

PlayerMP::PlayerMP(IWorld * world, Vector3 position):
	Actor(world, "MP", position, Capsule(Vector3(0, 0, 0), 0))
{
	mTextHandle = LoadGraph("./res/Texture/MP.png");
	mSlashHandle = LoadGraph("./res/Texture/Slash.png");
	num = NumberTexture("./res/Texture/num.png", 10, 10, 1, 16, 32);
}

void PlayerMP::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mMPValue = ((Player*)player)->GetMP();
	mMaxMPValue = ((Player*)player)->GetMaxMP();
}

void PlayerMP::onDraw() const
{
	DrawGraph(mPosition.x, mPosition.y, mTextHandle, TRUE);
	//êîéö
	{
		Vector3 numpos(mPosition.x + 64, mPosition.y, 0);
		num.Draw(numpos, mMPValue);
	}
	//ç≈ëÂ
	{
		Vector3 pos = Vector3(mPosition.x + 60 + (16 * (int)std::to_string(mMPValue).size()), mPosition.y, 0);
		DrawGraph(pos.x, pos.y, mSlashHandle, TRUE);
		Vector3 numpos(pos.x + 20, mPosition.y, 0);
		num.Draw(numpos, mMaxMPValue);
	}
}
