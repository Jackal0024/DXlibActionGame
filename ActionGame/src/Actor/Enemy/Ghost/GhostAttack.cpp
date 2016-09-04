#include "GhostAttack.h"

GhostArrack::GhostArrack(IWorld * world, const Vector3 & position, const Vector3& Velocity):
	Actor(world, "GolemAttack", position, { Vector3(0,0,0),3 }),
	mTimer(0.0f),
	m_Velocity(Velocity)
{
}

void GhostArrack::onUpdate(float deltaTime)
{
	mPosition += m_Velocity;
	if (mTimer > 3)
	{
		Dead();
	}
	mTimer += deltaTime;
}

void GhostArrack::onDraw() const
{
	mBody.Move(mPosition).Draw();
}

void GhostArrack::onCollide(Actor & other)
{
	Dead();
}
