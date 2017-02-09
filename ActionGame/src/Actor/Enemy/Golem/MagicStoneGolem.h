#pragma once

#include"../../Base/Actor.h"
#include"../../../Animation/Animator.h"
#include"../../Magic/Base/MagicList.h"
#include"../../../Effect/Base/Effect.h"

class MagicStoneGolem : public Actor
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
	MagicStoneGolem(IWorld* world, Vector3 position);
	MagicStoneGolem(IWorld* world, Vector3 position, Vector3 rotate,MagicList type);
	~MagicStoneGolem();

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
	bool isFront(float forward_dot_target);

	void Hit(float damage);

private:
	int mModel = 0;
	Animator mAnimator;
	Motion mMotionid;
	State mState;
	ActorPtr mTarget;
	float mHitPoint;
	//魔法攻撃するか？
	bool isMagicAttack;
	//どの魔法攻撃をするか？
	MagicList mMagicType;
	IEffect mHitEffect;
};
