#include "DeadEffect.h"
#include"../FadeEffect.h"
#include"DeadTexture.h"
#include"../../../System/ConstantList/WindowSize.h"

DeadEffect::DeadEffect(IWorld * world):
	Actor(world, "Dead", {0,0,0}, Capsule(Vector3(0, 0, 0), 0))
{
	mFade = std::make_shared<Fadeeffect>(mWorld, 0.0f, 255.0f, 2.0f, GetColor(0, 0, 0));
	mFade->AddChild(std::make_shared<DeadTexture>(mWorld,mFade));
	mWorld->AddActor(ActorGroup::TOPUI, mFade);
}
