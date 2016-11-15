#include "RockBlast.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"

RockBlast::RockBlast(IWorld * world, Vector3 position, const Vector3 & velocity, Tag tag):
	Actor(world,"Rock",position, { Line(position,position + Vector3(0,0,0)),10.0f },tag),
	mTimer(0.0f),
	mAtkPower(30),
	mVelocity(velocity),
	mGravity(0,0,0),
	mHit(false)
{
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Rock"));
}

RockBlast::~RockBlast()
{
	MV1DeleteModel(mModelHandle);
}

void RockBlast::onUpdate(float deltaTime)
{
	mVelocity = VNorm(mVelocity);
	mGravity += Vector3(0, -1.0f, 0) * deltaTime;
	mPosition += (mVelocity) * 3;
	mPosition += mGravity;
	if (mTimer > 4 || mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 0, 0), mBody.mRadius))
	{
		Dead();
	}
	mTimer += deltaTime;
}

void RockBlast::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(mTimer), GetPose().SetScale(Vector3(0.8f,0.8f,0.8f))));
	MV1DrawModel(mModelHandle);
	//mBody.Move(mPosition).Draw();
}

void RockBlast::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		other.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&mAtkPower);
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		if (!mHit)
		{
			mHit = true;
			mWorld->SendMsg(EventMessage::PLAYER_MAGICUP);
		}
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&mAtkPower);
	}
}