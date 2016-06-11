#include "Golem.h"

Golem::Golem(IWorld & world, Vector3 position):
	Actor(world, "Golem", position, {5.0f})
{
	
}

void Golem::onStart()
{
	mModel = MV1LoadModel("./res/golem/golem.pmx");
}

void Golem::onUpdate(float deltaTime)
{
}

void Golem::onDraw() const
{
	MV1SetPosition(mModel, mPosition);
	MV1DrawModel(mModel);

}

void Golem::onCollide(Actor & other)
{
	Dead();
}
