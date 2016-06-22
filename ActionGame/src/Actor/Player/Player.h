#ifndef PLAYER_H_
#define PLAYER_H_

#include"../Base/Actor.h"
#include"../../Animation/Animator.h"

class Player : public Actor
{
public:
	Player(IWorld& world, Vector3 position);

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	int mModelHandle;
	Animator mAnimator;

};

#endif