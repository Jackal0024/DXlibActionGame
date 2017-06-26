#include "HPBar.h"
#include"../../Player/Player.h"

HPBar::HPBar(IWorld * world, Vector3 position) :
	Actor(world, "HP", position, Capsule(Vector3(0, 0, 0), 0))
{
}

HPBar::~HPBar()
{
}

void HPBar::onUpdate(float deltaTime)
{
	auto player = (Player*)mWorld->FindActor("Player").get();
	mHPValue = player->GetHP();
	if (mHPValue != mPrevHP)
	{
		mPrevHP = max(mHPValue,mPrevHP - (30 * deltaTime) );

		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mPrevHP / mMaxHP) * (mMaxHP + 50);
		mSlipBar_rb = Vector3(lt.x + l, lt.y + 15, 0);
	}
	mMaxHP = player->GetMaxHp();
}

void HPBar::onDraw() const
{
	{
		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mHPValue / mMaxHP) * (mMaxHP + 50);
		Vector3 rb = Vector3(lt.x + l, lt.y + 15, 0);

		//最大HPのbar数値
		Vector3 crb = Vector3(lt.x + mMaxHP + 50, lt.y + 15, 0);

		//最大HPBAR
		DrawBox((int)lt.x, (int)lt.y, (int)crb.x, (int)crb.y, GetColor(0, 0, 155), true);

		//ダメージを受けた時の表示
		DrawBox((int)lt.x, (int)lt.y, (int)mSlipBar_rb.x, (int)mSlipBar_rb.y, GetColor(128, 128, 0), true);

		//現在HPのBAR
		DrawBox((int)lt.x, (int)lt.y, (int)rb.x, (int)rb.y, GetColor(255, 0, 0), true);
	}
}
