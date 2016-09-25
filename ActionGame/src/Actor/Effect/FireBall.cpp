#include "FireBall.h"
#include"FireParts.h"

FireBall::FireBall(IWorld * world, Vector3 position, const Vector3& Velocity) :
Actor(world, "Fire", position, { Line(position,position + Vector3(0,0,0)),3.0f }),
mVelocity(Velocity),
mTimer(0),
mIndex(0)
{
	LoadDivGraph("./res/Particles/FireTexture2.png", 32, 8, 4, 128, 128, mHandle);
}

FireBall::~FireBall()
{
}

void FireBall::onUpdate(float deltaTime)
{
	mIndex = (mIndex + 1) % 32;
	mVelocity = VNorm(mVelocity);
	mPosition += mVelocity * 4;
	if (mTimer > 1)
	{
		Dead();
	}
	mTimer += deltaTime;
	//mWorld->AddActor(ActorGroup::Effect, std::make_shared<FirePats>(mWorld, mPosition));
}

void FireBall::onDraw() const
{
	DrawBillboard3D(mPosition, 0.5f, 0.5f, 32, 0, mHandle[mIndex], TRUE);
}

void FireBall::onCollide(Actor & other)
{
	Dead();
}
