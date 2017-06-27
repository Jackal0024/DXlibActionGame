/*
*ゴブリンクラス
*概要：ボス級の敵、ゴブリンのクラス
*/
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
	//コンストラクタ
	Goblin(IWorld* world, Vector3 position);
	//コンストラクタ
	Goblin(IWorld* world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower);
	//デストラクタ
	~Goblin();

private:
	//開始処理
	void onStart() override;
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& other) override;
	//イベントを受け取った時の処理
	void onMessage(EventMessage message, void* p) override;

private:
	//ステートの更新
	void StateUpdate(float deltaTime);
	//ステートをチェンジ
	void StateChange(State nextState, Motion nextMotion = Motion::IDLE_MOTION);
	//アイドル時の処理
	void IdleProcess(float deltaTime);
	//移動時の処理
	void MoveProcess(float deltaTime);
	//走る時の処理
	void RunProcess(float deltaTime);
	//強攻撃の処理
	void HeavyAttackProcess(float deltaTime);
	//弱攻撃の処理
	void LightAttackProcess(float deltaTime);
	//死亡時の処理
	void DeadProcess(float deltaTime);
	//ダメージ時の処理
	void DamageProcess(float deltaTime);
	//攻撃を受けた時の処理
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