#include "GolemAttack.h"
#include"../../Base/HitInfo.h"

EnemyArrack::EnemyArrack(IWorld * world, const Vector3 & position):
	Actor(world,"GolemAttack",position,{ Vector3(0,2,0),7 },Tag::ENEMY_ATTACK),
	mTimer(0.0f),
	mAtk(40)
{
}

void EnemyArrack::onUpdate(float deltaTime)
{
	mPosition += Vector3(0, -0.5f, 0);
	if (mTimer > 1)
	{
		Dead();
	}
	mTimer += deltaTime;
}

void EnemyArrack::onDraw() const
{
	mBody.Move(mPosition).Draw();
}

void EnemyArrack::onCollide(Actor & othr)
{
	if (othr.GetTag() == Tag::PLAYER)
	{
		Hitinfo hit = { mPosition,mAtk };
		othr.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
		Dead();
	}
}
