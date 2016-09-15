#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"

class Ghost : public Actor
{
public:
	enum State
	{
		IDLE,
		ATTACK,
		DAMAGE,
		DEAD
	};

public:
	Ghost(IWorld* world, Vector3 position);
	Ghost(IWorld* world, Vector3 position, Vector3 rotate);

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p);

private:
	void StateUpdate(float deltaTime);
	void Idle(float deltaTime);
	void Attack(float deltaTime);
	void DeadState(float deltaTime);
	void Damage(float deltaTime);
	void StateChange(State nextState);

private:
	int mModel = 0;
	State mState;
	ActorPtr mTarget;
	float mY;
	float mTimer;
	float mAttackTimer;
};
