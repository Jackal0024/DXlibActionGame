#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"

class Lizard : public Actor
{
public:
	enum Motion
	{
		IDLE_MOTION = 0,
		MOVE_MOTION = 1,
		DAMAGE_MOTION = 2,
		DEAD_MOTION = 3,
		ATTACK_MOTION = 4
	};

	enum State
	{
		IDLE,
		CAUTION,
		DISCOVERY,
		ATTACK,
		DAMAGE,
		DEAD
	};

public:
	Lizard(IWorld* world, Vector3 position);
	Lizard(IWorld* world, Vector3 position, Vector3 rotate);
	~Lizard();

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void StateUpdate(float deltaTime);
	void StateChange(State nextState, Motion nextMotion);

	void IdleProcess(float deltaTime);
	void CautionProcess(float deltaTime);
	void DiscoveryProcess(float deltaTime);
	void AttackProcess(float deltaTime);
	void DeadProcess(float deltaTime);
	void DamageProcess(float deltaTime);

	void Hit(float damage);

private:
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	float mHitPoint;

	Vector3 mCenterPosition;
	Vector3 mVelocity;
	float mTimer;

};
