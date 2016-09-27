#include "FireBall.h"
#include"../../Player/Player.h"

FireBall::FireBall(IWorld * world, Vector3 position, const Vector3& Velocity,Tag tag) :
Actor(world, "Fire", position, { Line(position,position + Vector3(0,0,0)),10.0f },tag),
mVelocity(Velocity),
mTimer(0),
mIndex(0),
mAtkPower(5)
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
	if (mTimer > 1 || mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 0, 0), mBody.mRadius))
	{
		Dead();
	}
	mTimer += deltaTime;
}

void FireBall::onDraw() const
{
	DrawBillboard3D(mPosition, 0.5f, 0.5f, 32, 0, mHandle[mIndex], TRUE,TRUE);
}

void FireBall::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		other.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&mAtkPower);
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&mAtkPower);
	}
	Dead();
}