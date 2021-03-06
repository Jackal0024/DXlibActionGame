#include "Mummy.h"
#include"MummyAttack.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../Magic/FireBall/FireBall.h"
#include"../../../AssetStorage/EffectStorage.h"

Mummy::Mummy(IWorld * world, Vector3 position) :
	Actor(world, "Mummy", position, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStateTimer(0.0f),
	mStateBool(false),
	mStartHitPoint(60),
	mAttackPower(40),
	isPartner(false)
{
	mHitEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
	mHitPoint = mStartHitPoint;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Mummy"));
}

Mummy::Mummy(IWorld * world, Vector3 position, Vector3 rotate, bool isPartner, float startHitPoint, float attackPower) :
	Actor(world, "Mummy", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStateTimer(0.0f),
	mStateBool(false),
	mStartHitPoint(startHitPoint),
	mAttackPower(attackPower),
	isPartner(isPartner)
{
	mHitEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
	mHitPoint = mStartHitPoint;
	if(isPartner) mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("GoblinGuardMummy"));
	else mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Mummy"));
}

void Mummy::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);
	PartnerSearch();
}

void Mummy::onUpdate(float deltaTime)
{
	PartnerSearch();
	mTarget = mWorld->FindActor("Player");

	StateUpdate(deltaTime);

	mAnimator.Update(deltaTime);
}

void Mummy::onDraw() const
{
	//モデルデータが前後ろ逆なため描画時１８０度回転する
	MV1SetMatrix(mModel, Matrix::CreateRotationY(180) * GetPose());
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void Mummy::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::ENEMY)
	{
		Vector3 sub = mPosition - other.GetPosition();
		sub = VNorm(sub);
		mPosition += sub;
	}
}

void Mummy::onMessage(EventMessage message, void * p)
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

void Mummy::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: IdleProcess(deltaTime); break;
	case State::MOVE: MoveProcess(deltaTime); break;
	case State::MAGIC: MagicProcess(deltaTime) ; break;
	case State::KICK: KickProcess(deltaTime) ; break;
	case State::DAMAGE: DamageProcess(deltaTime); break;
	case State::DEAD: DeadProcess(deltaTime); break;
	}
	mStateTimer += deltaTime;
}

void Mummy::StateChange(State nextState, Motion nextMotion)
{
	mState = nextState;
	mMotionid = nextMotion;
	mStateTimer = 0.0f;
	mStateBool = false;
}

/*
*	優先1:パートナーから遠くなったら近づく
*	優先2:敵が蹴りの範囲
*	優先3:敵が魔法の射程範囲なら魔法攻撃
*/
void Mummy::IdleProcess(float deltaTime)
{
	mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
	Vector3 targetsub = mTarget->GetPosition() - mPosition;

	if (VSize(targetsub) > 10 && VSize(targetsub) < 100)
	{
		StateChange(State::MAGIC);
	}
	else if (VSize(targetsub) < 10)
	{
		StateChange(State::KICK);
	}

	if (mPartner)
	{
		Vector3 partnersub = mPartner->GetPosition() - mPosition;
		if (VSize(partnersub) > 80 && mStateTimer > 1)
		{
			StateChange(State::MOVE);
		}
	}
}

void Mummy::MoveProcess(float deltaTime)
{
	if (mPartner)
	{
		Vector3 partnersub = mPartner->GetPosition() - mPosition;

		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		float rad = atan2(partnersub.x, partnersub.z);

		Vector3 velocity = VNorm(partnersub) * deltaTime;
		velocity = velocity * VSize(partnersub);
		mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, velocity);
		mPosition += velocity;
		mRotate = MGetRotY(rad);
		if (VSize(partnersub) < 40 && mStateTimer < 4)
		{
			StateChange(State::IDLE);
		}
	}
	else
	{
		StateChange(State::IDLE);
	}
}

void Mummy::MagicProcess(float deltaTime)
{
	Vector3 targetsub = mTarget->GetPosition() - mPosition;

	mAnimator.AnimationChange(Motion::MAGIC_MOTION, 0.3f, 0.5f, false);

	float dot = VDot(VNorm(targetsub), Vector3(0, 0, 1));
	float rad = atan2(targetsub.x, targetsub.z);
	mRotate = MGetRotY(rad);

	if (mStateTimer > 1.0f && !mStateBool)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<FireBall>(mWorld, mPosition, VNorm(targetsub), Tag::ENEMY_ATTACK, mAttackPower));
		mStateBool = true;
	}

	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Mummy::KickProcess(float deltaTime)
{
	Vector3 targetsub = mTarget->GetPosition() - mPosition;

	mAnimator.AnimationChange(Motion::KICK_MOTION, 0.3f, 0.5f, false);

	float rad = atan2(targetsub.x, targetsub.z);

	mRotate = MGetRotY(rad);

	//攻撃
	if (mStateTimer > 0.3f && !mStateBool)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<MummyAttack>(mWorld, mPosition
			+ (mRotate.Forward() * 10),
			mAttackPower));
	}

	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Mummy::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		//mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void Mummy::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Mummy::Hit(float damage)
{
	mHitPoint -= damage;
	mHitEffect.Play();
	mHitEffect.SetPosition(mPosition + Vector3(0, 10, 0));
	if (mHitPoint <= 0)
	{
		mBody.isAlive = false;
		SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DEAD, Motion::DEAD_MOTION);
	}
	else
	{
		mAnimator.AnimationChange(Motion::MIN_DAMAGE_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DAMAGE, Motion::MIN_DAMAGE_MOTION);
	}
}

void Mummy::PartnerSearch()
{
	if (!isPartner)
	{
		mPartner = nullptr;
		return;
	}
	if (mWorld->FindActor("Goblin"))
	{
		mPartner = mWorld->FindActor("Goblin");
	}
	else
	{
		mPartner = nullptr;
	}
}
