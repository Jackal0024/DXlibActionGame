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
		ATTACK,
		DAMAGE
	};
public:
	Player(IWorld* world, Vector3 position);
	Player(IWorld* world, Vector3 position,Vector3 rotate);
	float GetHP();
	float GetMaxHp();
	float GetMP();
	float GetMaxMP();

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
	void Damege(float deltaTime);

private:
	int mModelHandle;
	int mWeaponHandle;
	State mState;
	Animator mAnimator;
	float mHitPoint;
	float mMagicPoint;
	float mStateTimer;
	Vector3 mVelocity;

private:
	const float MAXHP = 100;
	const float MAXMP = 100;

};

#endif