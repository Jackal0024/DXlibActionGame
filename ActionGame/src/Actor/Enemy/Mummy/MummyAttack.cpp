#include "MummyAttack.h"
#include "../../Base/HitInfo.h"

MummyAttack::MummyAttack(IWorld * world, const Vector3 & position):
	Actor(world, "MummyAttack", position, { Vector3(0,2,0),7 }, Tag::ENEMY_ATTACK),
	mTimer(0.0f),
	mAtk(10)
{
}

void MummyAttack::onUpdate(float deltaTime)
{
	if (mTimer > 0.3f)
	{
		Dead();
	}
	mTimer += deltaTime;
}

void MummyAttack::onDraw() const
{
	mBody.Move(mPosition).Draw();
}

void MummyAttack::onCollide(Actor & othr)
{
	if (othr.GetTag() == Tag::PLAYER)
	{
		Hitinfo hit = { mPosition,mAtk };
		othr.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
		Dead();
	}
}
