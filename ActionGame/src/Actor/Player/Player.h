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
	float GetMagicInterval();
	float GetAtk();

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void StateChange(State state);
	void StateUpdate(float deltaTime);

	void MoveProcess(float deltaTime);
	void AttackProcess(float deltaTime);
	void DamegeProcess(float deltaTime);

	Matrix SetModelFramePosition(int ModelHandle, char *FrameName, int SetModelHandle) const;
	void Hit(float damege);

	void ATKCharge(float deltaTime);
	void MagicCharge(float deltaTime);



private:
	int mModelHandle;
	int mWeaponHandle;
	State mState;
	Animator mAnimator;
	float mHitPoint;
	float mMagicPoint;
	float mStateTimer;
	Vector3 mVelocity;

	float mAtk;
	float mMagicInterval;

private:
	const float MAXHP = 100;
	const float MAXMP = 100;

};

#endif