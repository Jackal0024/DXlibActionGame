#include "Bomb.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../../AssetStorage/EffectStorage.h"
#include"../../Base/HitInfo.h"

Bomb::Bomb(IWorld * world, Vector3 position, Tag tag,float atk) :
	Actor(world, "Bomb", position, { Line(position,position + Vector3(0,0,0)),15.0f }, tag),
	mTimer(0.0f),
	mAtkPower(atk),
	mHit(false)
{
	mBombEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::MagicMineEffect));
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Bomb"));
	mBombEffect.Play();
	mBombEffect.SetPosition(mPosition);
}

Bomb::~Bomb()
{
	MV1DeleteModel(mModelHandle);
}

void Bomb::onUpdate(float deltaTime)
{
	if (mTimer > 1)
	{
		Dead();
	}
	mTimer += deltaTime;
	//mBody.mRadius += 20 * deltaTime;
}

void Bomb::onDraw() const
{
	//Vector3 scale = Vector3(mBody.mRadius * 0.3f, mBody.mRadius* 0.3f, mBody.mRadius* 0.3f);
	//MV1SetMatrix(mModelHandle, MGetRotY(180 * DX_PI / 180) * GetPose().SetScale(scale));
	//MV1DrawModel(mModelHandle);
	//mBody.Move(mPosition).Draw();
}

void Bomb::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		auto sub = mWorld->FindActor("Player")->GetPosition() - mPosition;
		Hitinfo hit = { VNorm(sub),mAtkPower };
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
