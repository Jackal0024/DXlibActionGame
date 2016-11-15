#include "FireWallParts.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"

FireWallParts::FireWallParts(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag):
	Actor(world, "Rock", position, { Line(position,position + Vector3(0,3,0)),10.0f }, tag),
	mTimer(0.0f),
	mVelocity(Velocity),
	mAtkPower(10.0f),
	mHit(false)
{
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("FireWall"));
}

FireWallParts::~FireWallParts()
{
	MV1DeleteModel(mModelHandle);
}

void FireWallParts::onUpdate(float deltaTime)
{
	mVelocity = VNorm(mVelocity);
	mPosition += (mVelocity)* 2;
	if (mTimer > 4 || mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 0, 0), mBody.mRadius))
	{
		Dead();
	}

	Vector3 h;
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}

	mTimer += deltaTime;
}

void FireWallParts::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(mTimer), GetPose().SetScale(Vector3(0.8f, 0.8f, 0.8f))));
	MV1DrawModel(mModelHandle);
	//mBody.Move(mPosition).Draw();
}

void FireWallParts::onCollide(Actor & other)
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