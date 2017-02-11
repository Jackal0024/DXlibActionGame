#ifndef GOLEM_H_
#define GOLEM_H_

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"
#include"../../Magic/Base/MagicList.h"
#include"../../../Effect/Base/Effect.h"

class Golem : public Actor
{
public:
	enum Motion
	{
		DAMAGE_MOTION = 4,
		IDLE_MOTION = 3,
		MOVE_MOTION = 2,
		DEAD_MOTION = 1,
		ATTACK_MOTION = 0
	};

	enum State
	{
		IDLE,
		MOVE,
		ATTACK,
		DAMAGE,
		DEAD
	};

public:
	Golem(IWorld* world, Vector3 position);
	Golem(IWorld* world, Vector3 position,Vector3 rotate, float startHitPoint,float attackPower);
	~Golem();

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
	void MoveProcess(float deltaTime);;
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
	float mHitPoint = 0;
	IEffect mEffect;

	float mStartHitPoint;
	float mAttackPower;
};

#endif
