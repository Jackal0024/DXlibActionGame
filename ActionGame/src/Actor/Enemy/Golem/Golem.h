/*
*ゴーレムクラス
*概要：ザコ敵１のゴーレムクラス
*/
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
	//コンストラクタ
	Golem(IWorld* world, Vector3 position);
	//コンストラクタ
	Golem(IWorld* world, Vector3 position,Vector3 rotate, float startHitPoint,float attackPower);
	//デストラクタ
	~Golem();

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
	//状態の更新
	void StateUpdate(float deltaTime);
	//状態のチェンジ
	void StateChange(State nextState, Motion nextMotion);
	//待機時の処理
	void IdleProcess(float deltaTime);
	//移動時の処理
	void MoveProcess(float deltaTime);;
	//攻撃時の処理
	void AttackProcess(float deltaTime);
	//死亡時の処理
	void DeadProcess(float deltaTime);
	//ダメージ時の処理
	void DamageProcess(float deltaTime);
	//攻撃を受けた時の処理
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
