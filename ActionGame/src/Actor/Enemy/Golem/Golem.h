#ifndef GOLEM_H_
#define GOLEM_H_

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"

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
	Golem(IWorld* world, Vector3 position,Vector3 rotate);

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	void StateUpdate(float deltaTime);
	void Idle(float deltaTime);
	void Move(float deltaTime);;
	void Attack(float deltaTime);
	void DeadState(float deltaTime);
	void Damage(float deltaTime);
	void StateChange(State nextState, Motion nextMotion);

private:
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	float mHitPoint;
};

#endif
