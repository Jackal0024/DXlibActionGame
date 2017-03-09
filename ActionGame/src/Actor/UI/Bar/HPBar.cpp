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
	auto player = mWorld->FindActor("Player").get();
	mHPValue = ((Player*)player)->GetHP();
	if (mHPValue != mPrevHP)
	{
		mPrevHP = max(mHPValue,mPrevHP - (30 * deltaTime) );

		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mPrevHP / mMaxHP) * (mMaxHP + 50);
		mSlipBar_rb = Vector3(lt.x + l, lt.y + 15, 0);
	}
	mMaxHP = ((Player*)player)->GetMaxHp();
}

void HPBar::onDraw() const
{
	{
		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mHPValue / mMaxHP) * (mMaxHP + 50);
		Vector3 rb = Vector3(lt.x + l, lt.y + 15, 0);

		//�ő�HP��bar���l
		Vector3 crb = Vector3(lt.x + mMaxHP + 50, lt.y + 15, 0);

		//�ő�HPBAR
		DrawBox(lt.x, lt.y, crb.x, crb.y, GetColor(0, 0, 155), true);

		//�_���[�W���󂯂����̕\��
		DrawBox(lt.x, lt.y, mSlipBar_rb.x, mSlipBar_rb.y, GetColor(128, 128, 0), true);

		//����HP��BAR
		DrawBox(lt.x, lt.y, rb.x, rb.y, GetColor(255, 0, 0), true);
	}
}
