#include "Hint.h"

Hint::Hint(IWorld * world, std::string name, Vector3 & position)
{
	mModelHandle = MV1LoadModel("./res/Hint/Hint.mv1");
}

Hint::~Hint(){}

void Hint::onUpdate(float deltaTime)
{
}

void Hint::onDraw() const
{
}

void Hint::onCollide(Actor & other)
{
}

void Hint::onMessage(EventMessage message, void * p)
{
}
