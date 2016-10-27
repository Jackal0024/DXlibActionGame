#include "SpearCircle.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"BlackSpear.h"

SpearCircle::SpearCircle(IWorld * world, Vector3 position, Tag tag) :
	Actor(world, "SpearCircle", position, { { 0,0,0 },3.0f }, tag),
	mTimer(0.0f)
{
	mModelHandle = AssetStorage::getInstance().GetHandle("SpearCircle");
}

SpearCircle::~SpearCircle()
{
	MV1DeleteModel(mModelHandle);
}

void SpearCircle::onUpdate(float deltaTime)
{
	if (mTimer > 10)
	{
		Dead();
	}
	mTimer += deltaTime;
}

void SpearCircle::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(mTimer), GetPose().SetScale(Vector3(0.8f, 0.8f, 0.8f))));
	MV1DrawModel(mModelHandle);
}

void SpearCircle::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<BlackSpear>(mWorld, mPosition, mTag));
		Dead();
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<BlackSpear>(mWorld, mPosition, mTag));
		Dead();
	}
}
