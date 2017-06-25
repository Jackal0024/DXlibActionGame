#include "IceNeedle.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../../AssetStorage/EffectStorage.h"
#include"../../Base/HitInfo.h"
#include"Math\MathHelper.h"

IceNeedle::IceNeedle(IWorld * world, Vector3 position, Vector3 velocity, int num,Tag tag, float atk):
	Actor(world, "AttackProcess",position - Vector3(0,30,0), { Vector3(0,15,0),5 },tag),
	mVelocity(velocity),
	mNum(num),
	mLifeTimer_(1),
	mDestination(position),
	isNext(false),
	mAtkPower(atk)
{
	mIceEffect = EffectStorage::getInstance().GetHandle(EffectList::IceNeedleEffect);
	SoundManager::getInstance().Play("./res/Sound/Ice.mp3");
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("IceNeedle"));
	mIceEffect.Play();
}

void IceNeedle::onUpdate(float deltaTime)
{
	mNum--;
	mLifeTimer_ -= deltaTime;
	mPosition = Vector3::Lerp(mPosition, mDestination, 0.05);
	mIceEffect.SetPosition(mPosition);
	if (mLifeTimer_ <= 0)
	{
		mIceEffect.Stop();
		Dead();
	}
	if (mNum > 0 && !isNext)
	{
		mVelocity.y = 0;
		Vector3 nextPos = mDestination + (mVelocity * 20);
		if (mTag == Tag::ENEMY_ATTACK)
		{
			mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<IceNeedle>(mWorld, nextPos, mVelocity, mNum, mTag,mAtkPower));
		}
		else
		{
			mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld, nextPos, mVelocity, mNum, mTag,mAtkPower));
		}
		isNext = true;
	}

	Vector3 h;
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}
}

void IceNeedle::onDraw() const
{

	MV1SetMatrix(mModelHandle,GetPose().Scale({0.05f,0.05f,0.05f}) );
	MV1DrawModel(mModelHandle); 
	//mBody.Move(mPosition).Draw();
}

void IceNeedle::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		Hitinfo hit = { VNorm(mVelocity),mAtkPower};
		other.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
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
