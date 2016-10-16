#include "Goblin.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"

Goblin::Goblin(IWorld * world, Vector3 position):
	Actor(world, "Goblin", position, { { 0,10,0 },4.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE)
{
	mHitPoint = 60;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Goblin"));
}

Goblin::Goblin(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Goblin", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE)
{
	mHitPoint = 60;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Goblin"));
}

Goblin::~Goblin()
{
}

void Goblin::onStart()
{
}

void Goblin::onUpdate(float deltaTime)
{
}

void Goblin::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	mBody.Translate(mPosition).Draw();
}

void Goblin::onCollide(Actor & other)
{
}

void Goblin::onMessage(EventMessage message, void * p)
{
}

void Goblin::StateUpdate(float deltaTime)
{
}

void Goblin::StateChange(State nextState, Motion nextMotion)
{
}
