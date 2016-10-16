#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"

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
		ATTACK,
		DAMAGE,
		DEAD
	};

public:
	Goblin(IWorld* world, Vector3 position);
	Goblin(IWorld* world, Vector3 position, Vector3 rotate);
	~Goblin();

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void StateUpdate(float deltaTime);
	void StateChange(State nextState, Motion nextMotion);

private:
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	float mHitPoint;

};