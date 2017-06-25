#include "MagicMine.h"
#include"Bomb.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../../Sound/SoundManager.h"
#include"../../Base/HitInfo.h"

MagicMine::MagicMine(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag,float power):
	Actor(world, "Mine", position, { Line(position,position + Vector3(0,0,0)),3.0f }, tag),
	mVelocity(Velocity),
	mTimer(0.0f),
	mHit(false),
	mPower(power)
{
	SoundManager::getInstance().Play("./res/Sound/MagicMine1.mp3");
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Mine"));

	float dot = VDot(VNorm(mVelocity), Vector3(0, 0, 1));
	float rad = atan2(mVelocity.x, mVelocity.z);
	mRotate = MGetRotY(rad);
}

MagicMine::~MagicMine()
{
	MV1DeleteModel(mModelHandle);
}

void MagicMine::onUpdate(float deltaTime)
{
	mVelocity = VNorm(mVelocity) * 2;

	Vector3 h;
	if (mWorld->GetField().Collision(mPosition, mPosition + mVelocity * 3,h))
	{
		mHit = true;
	}

	if (!mHit) mPosition += (mVelocity);

	if (mTimer > 5)
	{
		Explosion();
		Dead();
	}
	mTimer += deltaTime;
}

void MagicMine::onDraw() const
{
	MV1SetMatrix(mModelHandle,GetPose());
	MV1DrawModel(mModelHandle);
	//mBody.Move(mPosition).Draw();
}

void MagicMine::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		Explosion();
		Dead();
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		Explosion();
		Dead();
	}
}

void MagicMine::Explosion()
{
	SoundManager::getInstance().Play("./res/Sound/MagicMine2.mp3");
	if (mTag == Tag::ENEMY_ATTACK)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<Bomb>(mWorld, mPosition, mTag,mPower));
	}
	else
	{
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<Bomb>(mWorld, mPosition, mTag,mPower));
	}
}
