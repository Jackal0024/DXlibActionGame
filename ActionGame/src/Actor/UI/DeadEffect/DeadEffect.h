#pragma once

#include"../../Base/Actor.h"

class DeadEffect : public Actor
{
public:
	DeadEffect(IWorld* world);

private:
	ActorPtr mFade;
};
