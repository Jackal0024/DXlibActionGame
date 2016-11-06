#pragma once

#include"../../Base/Actor.h"

class WhiteEnd : public Actor
{
public:
	WhiteEnd(IWorld* world);
	void onUpdate(float deltaTime) override;

private:
	ActorPtr mFade;
};
