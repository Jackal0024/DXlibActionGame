#include "WhiteEnd.h"
#include"../FadeEffect.h"

WhiteEnd::WhiteEnd(IWorld * world):
	Actor(world, "Dead", { 0,0,0 }, Capsule(Vector3(0, 0, 0), 0))
{
	mFade = std::make_shared<Fadeeffect>(mWorld, 0.0f, 255.0f, 2.0f, GetColor(244, 244, 244));
	this->AddChild(mFade);
}

void WhiteEnd::onUpdate(float deltaTime)
{
	Fadeeffect* temp = (Fadeeffect*)mFade.get();
	if (temp->IsEnd())
	{
		mWorld->SendMsg(EventMessage::SCENE_END);
	}
}
