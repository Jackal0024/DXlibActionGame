#include "PointLight.h"

PointLight::PointLight(IWorld * world) :
	Actor(world, "PointLight", Vector3(0,0,0), { { 0,0,0 },0.0f })
{
}

void PointLight::onDraw() const
{
	ChangeLightTypePoint(mPosition , 600, 0.05f, 0.01f, 0.0006f);
}

void PointLight::onUpdate(float deltaTime)
{
	if (!mPlayer)
	{
		mPlayer = mWorld->FindActor("Player");
	}
	else
	{
		mPosition = mPlayer->GetPosition();
	}
}
