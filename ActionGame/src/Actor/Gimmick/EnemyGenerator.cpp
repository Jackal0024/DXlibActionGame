#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(IWorld * world, std::function<ActorPtr(void)> func) :
	Actor(world, "EnemyGenerator", {0,0,0}, { { 0,0,0 },3.0f }, Tag::UNTAGGET)
{
	mTarget = func();
	mGeneratorfunc = func;
	mBody.isAlive = false;
}

EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::ENEMY_GENERATOR:Generator(); break;
	}
}

void EnemyGenerator::Generator()
{
	if (mTarget->isDead())
	{
		mTarget = mGeneratorfunc();
	}
	else
	{
		mTarget->Dead();
		mTarget = mGeneratorfunc();
	}
}
