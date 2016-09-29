#ifndef PLAYERATTACK_H_
#define PLAYERATTACK_H_

#include"../Base/Actor.h"

class PlayerAttack : public Actor
{
public:
	PlayerAttack(IWorld* world, int weapon,float atk);

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	int mWeapoHandle;
	float mTimer;
	float mAtk;
};

#endif
