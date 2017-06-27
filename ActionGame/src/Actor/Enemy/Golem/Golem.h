/*
*�S�[�����N���X
*�T�v�F�U�R�G�P�̃S�[�����N���X
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
	//�R���X�g���N�^
	Golem(IWorld* world, Vector3 position);
	//�R���X�g���N�^
	Golem(IWorld* world, Vector3 position,Vector3 rotate, float startHitPoint,float attackPower);
	//�f�X�g���N�^
	~Golem();

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
	//��Ԃ̍X�V
	void StateUpdate(float deltaTime);
	//��Ԃ̃`�F���W
	void StateChange(State nextState, Motion nextMotion);
	//�ҋ@���̏���
	void IdleProcess(float deltaTime);
	//�ړ����̏���
	void MoveProcess(float deltaTime);;
	//�U�����̏���
	void AttackProcess(float deltaTime);
	//���S���̏���
	void DeadProcess(float deltaTime);
	//�_���[�W���̏���
	void DamageProcess(float deltaTime);
	//�U�����󂯂����̏���
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
