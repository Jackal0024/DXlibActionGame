#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"
#include"../../../Effect/Base/Effect.h"

class Mummy : public Actor
{
public:
	enum Motion
	{
		KICK_MOTION,
		BIG_DAMAGE_MOTION,
		DEAD_MOTION,
		MAGIC_MOTION,
		MOVE_MOTION,
		MIN_DAMAGE_MOTION,
		IDLE_MOTION
	};

	enum State
	{
		IDLE,
		MOVE,
		KICK,
		MAGIC,
		DAMAGE,
		DEAD
	};

public:
	Mummy(IWorld* world, Vector3 position);
	Mummy(IWorld* world, Vector3 position, Vector3 rotate);

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void StateUpdate(float deltaTime);
	void StateChange(State nextState, Motion nextMotion = Motion::IDLE_MOTION);

	void IdleProcess(float deltaTime);
	void MoveProcess(float deltaTime);
	void MagicProcess(float deltaTime);
	void KickProcess(float deltaTime);
	void DeadProcess(float deltaTime);
	void DamageProcess(float deltaTime);

	void Hit(float damage);
	void PartnerSearch();

private:
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	ActorPtr mPartner;
	float mHitPoint;
	float mStateTimer;
	bool mStateBool;

	IEffect mHitEffect;
};
