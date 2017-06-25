#include "Golem.h"
#include"GolemAttack.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../../AssetStorage/EffectStorage.h"

Golem::Golem(IWorld* world, Vector3 position):
	Actor(world, "Golem", position, { {0,10,0},3.0f },Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStartHitPoint(60),
	mAttackPower(40)
{
	mHitPoint = mStartHitPoint;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Golem"));
	mEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
}

Golem::Golem(IWorld * world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower) :
	Actor(world, "Golem", position,rotate,{ { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStartHitPoint(startHitPoint),
	mAttackPower(attackPower)
{
	mHitPoint = mStartHitPoint;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Golem"));
	mEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
}

Golem::~Golem()
{
	MV1DeleteModel(mModel);
}

void Golem::onStart()
{
	mAnimator.Initialize(mModel, mMotionid,true);

}

void Golem::onUpdate(float deltaTime)
{

	mPosition += Vector3(0, -0.1, 0);
	mTarget = mWorld->FindActor("Player");

	StateUpdate(deltaTime);

	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}

	mAnimator.Update(deltaTime);
	
}

void Golem::onDraw() const
{
	//���f���f�[�^���O���t�Ȃ��ߕ`�掞�P�W�O�x��]����
	MV1SetMatrix(mModel, Matrix::CreateRotationY(180) * GetPose());
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void Golem::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::ENEMY)
	{
		Vector3 sub = mPosition - other.GetPosition();
		sub = VNorm(sub);
		mPosition += sub;
	}
}

void Golem::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::ENEMY_DAMEGE:
		if (mState != State::DEAD && mState != State::DAMAGE)
		{
			float* damage = (float*)p;
			Hit(*damage);
		}
		break;
	}
}

void Golem::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: IdleProcess(deltaTime); break;
	case State::MOVE: MoveProcess(deltaTime); break;
	case State::ATTACK: AttackProcess(deltaTime); break;
	case State::DAMAGE: DamageProcess(deltaTime); break;
	case State::DEAD: DeadProcess(deltaTime); break;
	}
}

void Golem::IdleProcess(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis < 100)
	{
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::MOVE, Motion::MOVE_MOTION);
	}
}

void Golem::MoveProcess(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis > 100)
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE , Motion::IDLE_MOTION);
	}
	if (dis < 10)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<EnemyArrack>(mWorld, mPosition
			+ (mRotate.Forward() * 10)
			+ Vector3(0, 20, 0),
			mRotate.Forward(),
			mAttackPower));
		mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
		StateChange(State::ATTACK, Motion::ATTACK_MOTION);
	}

	if (mTarget)
	{
		Vector3 velocity = mTarget->GetPosition() - mPosition;

		float rad = atan2(velocity.x,velocity.z);

		velocity = VNorm(velocity) * deltaTime;
		mPosition += velocity * 15;
		mRotate = MGetRotY(rad);
	}
}

void Golem::AttackProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Golem::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		//mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void Golem::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Golem::Hit(float damage)
{
	mHitPoint -= damage;
	mEffect.Play();
	mEffect.SetPosition(mPosition + Vector3(0, 10, 0));
	if (mHitPoint <= 0)
	{
		mBody.isAlive = false;
		SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DEAD, Motion::DEAD_MOTION);
	}
	else
	{
		if (mState != State::ATTACK)
		{
			mAnimator.AnimationChange(Motion::DAMAGE_MOTION, 0.3f, 0.5f, false);
			StateChange(State::DAMAGE, Motion::DAMAGE_MOTION);
		}
	}
}

void Golem::StateChange(State nextState, Motion nextMotion)
{
	mState = nextState;
	mMotionid = nextMotion;
}
