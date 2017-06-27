/*
*�S�u�����N���X
*�T�v�F�{�X���̓G�A�S�u�����̃N���X
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
	//�R���X�g���N�^
	Goblin(IWorld* world, Vector3 position);
	//�R���X�g���N�^
	Goblin(IWorld* world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower);
	//�f�X�g���N�^
	~Goblin();

private:
	//�J�n����
	void onStart() override;
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& other) override;
	//�C�x���g���󂯎�������̏���
	void onMessage(EventMessage message, void* p) override;

private:
	//�X�e�[�g�̍X�V
	void StateUpdate(float deltaTime);
	//�X�e�[�g���`�F���W
	void StateChange(State nextState, Motion nextMotion = Motion::IDLE_MOTION);
	//�A�C�h�����̏���
	void IdleProcess(float deltaTime);
	//�ړ����̏���
	void MoveProcess(float deltaTime);
	//���鎞�̏���
	void RunProcess(float deltaTime);
	//���U���̏���
	void HeavyAttackProcess(float deltaTime);
	//��U���̏���
	void LightAttackProcess(float deltaTime);
	//���S���̏���
	void DeadProcess(float deltaTime);
	//�_���[�W���̏���
	void DamageProcess(float deltaTime);
	//�U�����󂯂����̏���
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