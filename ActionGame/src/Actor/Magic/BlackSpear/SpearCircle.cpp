#include "SpearCircle.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"BlackSpear.h"

SpearCircle::SpearCircle(IWorld * world, Vector3 position, Tag tag) :
	Actor(world, "SpearCircle", position, { { 0,0,0 },3.0f }, tag),
	mTimer(0.0f)
{
	SoundManager::getInstance().Play("./res/Sound/Trap.mp3");
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("SpearCircle"));
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
	Matrix mat = MGetRotY(mTimer) * GetPose();
	MV1SetMatrix(mModelHandle, mat);
	MV1DrawModel(mModelHandle);
}

void SpearCircle::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER && mTag == Tag::ENEMY_ATTACK)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<BlackSpear>(mWorld, mPosition, mTag));
		Dead();
	}
	if (other.GetTag() == Tag::ENEMY && mTag == Tag::PLAYER_ATTACK)
	{
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<BlackSpear>(mWorld, mPosition, mTag));
		Dead();
	}
}
