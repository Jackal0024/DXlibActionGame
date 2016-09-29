#include "PlayerHP.h"
#include"../Player/Player.h"

PlayerHP::PlayerHP(IWorld* world, Vector3 position):
	Actor(world, "HP", position, Capsule(Vector3(0,0,0),0))
{
	mTextHandle = LoadGraph("./res/Texture/HP.png");
	mSlashHandle = LoadGraph("./res/Texture/Slash.png");
	num = NumberTexture("./res/Texture/num.png", 10, 10, 1, 16, 32);
}

void PlayerHP::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mHPValue = ((Player*)player)->GetHP();
	mMaxHPValue = ((Player*)player)->GetMaxHp();
	mAtk = ((Player*)player)->GetAtk();
}

void PlayerHP::onDraw() const
{
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

	Vector3 lt = Vector3(mPosition.x + 15,mPosition.y + 35,0);
	float l = (mAtk / 20) * 155;
	Vector3 rb = Vector3(lt.x + l,lt.y + 5,0);

	DrawBox(lt.x, lt.y, rb.x, rb.y, GetColor(255, 0, 0), true);
}
