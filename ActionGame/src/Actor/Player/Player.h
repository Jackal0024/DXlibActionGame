#ifndef PLAYER_H_
#define PLAYER_H_

#include"../Base/Actor.h"
#include"../../Animation/Animator.h"


class Player : public Actor
{
public:
	enum State
	{
		MOVE,
		ATTACK
	};
public:
	Player(IWorld* world, Vector3 position);
	float GetHP();
	float GetMaxHp();

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	Matrix SetModelFramePosition(int ModelHandle, char *FrameName, int SetModelHandle) const;
	void StateChange(State state);
	void StateUpdate(float deltaTime);
	void Move(float deltaTime);
	void Attack(float deltaTime);

private:
	int mModelHandle;
	int mWeaponHandle;
	State mState;
	Animator mAnimator;
	float mHitPoint;

private:
	const float MAXHP = 100;

};

#endif