#include "BlackSpear.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"

BlackSpear::BlackSpear(IWorld * world, Vector3 position, Tag tag, float atk):
	Actor(world,"BlackSpear",position + Vector3(0,-30,0), { Line(position,position + Vector3(0,3,0)),10.0f }),
	mTimer(0.0f),
	mAtkPower(atk),
	mHit(false),
	mToPos(position)
{
	SoundManager::getInstance().Play("./res/Sound/Spear.mp3");
	mFromPos = mPosition;
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("BlackSpear"));
}

BlackSpear::~BlackSpear()
{
	MV1DeleteModel(mModelHandle);
}

void BlackSpear::onUpdate(float deltaTime)
{
	if (mTimer > 3)
	{
		Dead();
	}
	mPosition = Vector3::Lerp(mFromPos, mToPos, mTimer * 2);
	mTimer += deltaTime;
}

void BlackSpear::onDraw() const
{
	MV1SetMatrix(mModelHandle,GetPose());
	MV1DrawModel(mModelHandle);
}

void BlackSpear::onCollide(Actor & other)
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
		float damage = mAtkPower + MAGICPOWER;
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&damage);
	}
}
