#ifndef GOLEM_H_
#define GOLEM_H_

#include"../../Base/Actor.h"

class Golem : public Actor
{
public:
	Golem(IWorld& world, Vector3 position);

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	int mModel = 0;
};

#endif
