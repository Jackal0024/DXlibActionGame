#include "FireWall.h"
#include"FireWallParts.h"

FireWall::FireWall(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag) :
	Actor(world, "Rock", position, { Line(position,position + Vector3(0,0,0)),10.0f }, Tag::UNTAGGET)
{
	for (int i = 0; i < 5; i++)
	{
		Vector3 right = VTransform(Velocity, MGetRotY(90 * DX_PI / 180));
		Vector3 pos = mPosition + VNorm(right) * ((10 * i) - 20);
		if (mTag == Tag::ENEMY_ATTACK)
		{
			mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<FireWallParts>(mWorld, pos, Velocity, tag));
		}
		else
		{
			mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireWallParts>(mWorld, pos, Velocity, tag));
		}
	}
	Dead();
}

FireWall::~FireWall()
{
}
