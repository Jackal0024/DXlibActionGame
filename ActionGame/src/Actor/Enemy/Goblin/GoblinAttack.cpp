#include "GoblinAttack.h"
#include"../../Base/HitInfo.h"

GoblinAttack::GoblinAttack(IWorld * world, const Vector3 & position, float delay):
	Actor(world, "GoblinAttack", position, { Vector3(0,2,0),3 }, Tag::ENEMY),
	mTimer(0.0f),
	mAtk(10),
	mDelay(delay)
{
}

void GoblinAttack::onUpdate(float deltaTime)
{
	if (mTimer > mDelay + 0.1f) Dead();
	mTimer += deltaTime;
}

void GoblinAttack::onDraw() const
{
	mBody.Move(mPosition).Draw();
}

void GoblinAttack::onCollide(Actor & othr)
{
	//プレイヤーかつディレイ時間を超えている
	if (othr.GetTag() == Tag::PLAYER && (mTimer > mDelay))
	{
		Hitinfo hit = { mPosition,mAtk };
		othr.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
		Dead();
	}
}
