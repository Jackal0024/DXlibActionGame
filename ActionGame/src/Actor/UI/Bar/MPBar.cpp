#include "MPBar.h"
#include"../../Player/Player.h"

MPBar::MPBar(IWorld * world, Vector3 position) :
	Actor(world, "MP", position, Capsule(Vector3(0, 0, 0), 0))
{
}

MPBar::~MPBar()
{
}

void MPBar::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mMPValue = ((Player*)player)->GetMP();
	mMaxMP = ((Player*)player)->GetMaxMP();
}

void MPBar::onDraw() const
{
	{
		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mMPValue / mMaxMP) * mMaxMP;
		Vector3 rb = Vector3(lt.x + l, lt.y + 15, 0);

		Vector3 crb = Vector3(lt.x + mMaxMP, lt.y + 15, 0);
		DrawBox(lt.x, lt.y, crb.x, crb.y, GetColor(0, 0, 155), true);

		DrawBox(lt.x, lt.y, rb.x, rb.y, GetColor(0, 0, 255), true);
	}
}
