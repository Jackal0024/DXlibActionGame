#include "Golem.h"

Golem::Golem(IWorld & world, Vector3 position):
	Actor(world, "Golem", position, { {0,3.0f,0},1.0f })
{
	mModel = MV1LoadModel("./res/golem/golem.mv1");
}

void Golem::onStart()
{
	mRotate.SetScale({0.5f,0.5f,0.5f});
}

void Golem::onUpdate(float deltaTime)
{
	
	mPosition += Vector3(0, -0.1, 0);

	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}
	MV1SetMatrix(mModel, GetPose());
}

void Golem::onDraw() const
{
	
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void Golem::onCollide(Actor & other)
{
	Dead();
}
