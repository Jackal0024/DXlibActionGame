#pragma once

#include"../Base/Actor.h"

class WarpCircle :public Actor
{
public:
	WarpCircle(IWorld* world, Vector3 position);
	WarpCircle(IWorld* world, Vector3 position, Vector3 rotate);
private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p);

private:
	int mHandle;
	int mHandle2;
	bool isEnd;
	ActorPtr mTarget;
	float angel;

};
