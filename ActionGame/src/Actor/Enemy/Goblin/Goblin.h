#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"
#include"../../../Effect/Base/Effect.h"

class Goblin : public Actor
{
public:
	enum Motion
	{
		IDLE_MOTION,
		DEAD_MOTION,
		HEAVY_ATTACK_MOTION,
		LIGHT_ATTACK_MOTION,
		DAMAGE_MOTION,
		WALK_MOTION,
		RUN_MOTION,
	};

	enum State
	{
		IDLE,
		MOVE,
		RUN,
		HEAVY_ATTACK,
		LIGHT_ATTACK,
		DAMAGE,
		DEAD
	};

public:
	Goblin(IWorld* world, Vector3 position);
	Goblin(IWorld* world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower);
	~Goblin();

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
	void RunProcess(float deltaTime);
	void HeavyAttackProcess(float deltaTime);
	void LightAttackProcess(float deltaTime);
	void DeadProcess(float deltaTime);
	void DamageProcess(float deltaTime);

	void Hit(float damage);

private:
	float mStateTimer;
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	float mHitPoint;
	Vector3 mCenterPoint;
	IEffect mEffect;

	float mStartHitPoint;
	float mAttackPower;

};