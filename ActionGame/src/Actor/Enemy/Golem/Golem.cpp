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
	MV1SetScale(mModel,Vector3(0.2f,0.2f,0.2f));
}

void Golem::onDraw() const
{
	MV1SetMatrix(mModel, GetPose());
	MV1DrawModel(mModel);

}

void Golem::onCollide(Actor & other)
{
	Dead();
}
