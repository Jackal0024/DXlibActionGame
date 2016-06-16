#ifndef PLAYER_H_
#define PLAYER_H_

#include"../Base/Actor.h"

class Player : public Actor
{
public:
	Player(IWorld& world, Vector3 position);

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
};

#endif