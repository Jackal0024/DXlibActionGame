#include "PlayerHP.h"
#include"NumberTexture.h"
#include"../Player/Player.h"

PlayerHP::PlayerHP(IWorld* world, Vector3 position):
	Actor(world, "HP", position, Capsule(Vector3(0,0,0),0))
{
	mTextHandle = LoadGraph("./res/Texture/HP.png");
	mSlashHandle = LoadGraph("./res/Texture/Slash.png");
}

void PlayerHP::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mHPValue = ((Player*)player)->GetHP();
	mMaxHPValue = ((Player*)player)->GetMaxHp();
}

void PlayerHP::onDraw() const
{
	NumberTexture num("./res/Texture/num.png", 10, 10, 1, 16, 32);
	DrawGraph(mPosition.x, mPosition.y, mTextHandle, TRUE);
	//êîéö
	{
		Vector3 numpos(mPosition.x + 64, mPosition.y, 0);
		num.Draw(numpos, mHPValue);
	}
	//ç≈ëÂ
	{
		Vector3 pos = Vector3(mPosition.x + 60 + ( 16 * (int)std::to_string(mHPValue).size()), mPosition.y, 0);
		DrawGraph(pos.x, pos.y, mSlashHandle, TRUE);
		Vector3 numpos(pos.x + 20, mPosition.y, 0);
		num.Draw(numpos,mMaxHPValue);
	}
	//DrawGraph(mPosition.x, mPosition.y, mNumHandle[0], FALSE);
}
