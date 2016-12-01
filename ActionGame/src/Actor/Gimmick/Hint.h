#pragma once

#include"../Base/Actor.h"

class Hint : public Actor
{
public:
	Hint(IWorld* world, std::string name, Vector3& position);
	~Hint();

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;
private:
	float mTimer;
	int mModelHandle;
	int mHintTexture;
};
