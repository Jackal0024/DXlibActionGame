#pragma once

#include"../Base/Actor.h"

class HealCircle :public Actor
{
public:
	HealCircle(IWorld* world, Vector3 position);
	HealCircle(IWorld* world, Vector3 position, Vector3 rotate);
	~HealCircle();
private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p);

private:
	int mHandle;
	bool isHealing;
	ActorPtr mTarget;

};
