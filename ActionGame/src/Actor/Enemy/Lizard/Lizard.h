/*
*���U�[�h�}���N���X
*�T�v�F�U�R�G�Q�A����f��
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"
#include"../../../Effect/Base/Effect.h"

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
	Lizard(IWorld* world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower);
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

	bool isFront(float forward_dot_target);

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
	IEffect mHitEffect;

	float mStartHitPoint;
	float mAttackPower;


};
