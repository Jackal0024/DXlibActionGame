#include "Light.h"

Light::Light(IWorld* world, const Vector3 & position) :
	Actor(world, "DirectionalLight", position, { {0,0,0},0.0f })
{
}

void Light::onDraw() const
{
	ChangeLightTypeDir(mPosition);
}
