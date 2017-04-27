#include "Lizard.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../../Sound/SoundManager.h"
#include"../../Magic/FireBall/FireBall.h"
#include"../../../AssetStorage/EffectStorage.h"

Lizard::Lizard(IWorld * world, Vector3 position):
Actor(world, "Lizard", position, { { 0,10,0 },3.0f }, Tag::ENEMY),
mMotionid(Motion::IDLE_MOTION),
mState(State::IDLE),
mCenterPosition(position),
mTimer(0),
mStartHitPoint(100),
mAttackPower(40)
{
	mHitEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
	mHitPoint = mStartHitPoint;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Lizard"));
}

Lizard::Lizard(IWorld * world, Vector3 position, Vector3 rotate, float startHitPoint, float attackPower):
	Actor(world, "Lizard", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mCenterPosition(position),
	mTimer(0),
	mStartHitPoint(startHitPoint),
	mAttackPower(attackPower)
{
	mHitEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::HitEffect));
	mHitPoint = mStartHitPoint;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Lizard"));
}

Lizard::~Lizard()
{
	MV1DeleteModel(mModel);
}

void Lizard::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);
}

void Lizard::onUpdate(float deltaTime)
{
	//重力処理
	mPosition += Vector3(0, -0.1f, 0);
	mTarget = mWorld->FindActor("Player");

	StateUpdate(deltaTime);

	//壁の判定を二重にして絶対にステージ外に出ないように
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);

	//地面との判定
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}

	//アニメーションアップデート
	mAnimator.Update(deltaTime);
}

void Lizard::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void Lizard::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::ENEMY)
	{
		Vector3 sub = mPosition - other.GetPosition();
		sub = VNorm(sub);
		mPosition += sub;
	}
}

void Lizard::onMessage(EventMessage message, void * p)
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

void Lizard::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: IdleProcess(deltaTime); break;
	case State::CAUTION: CautionProcess(deltaTime); break;
	case State::DISCOVERY: DiscoveryProcess(deltaTime); break;
	case State::ATTACK: AttackProcess(deltaTime); break;
	case State::DAMAGE: DamageProcess(deltaTime); break;
	case State::DEAD: DeadProcess(deltaTime); break;
	}
}

void Lizard::StateChange(State nextState, Motion nextMotion)
{
	mState = nextState;
	mMotionid = nextMotion;
}

void Lizard::IdleProcess(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis < 100)
	{
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::DISCOVERY, Motion::MOVE_MOTION);
	}
	else
	{
		mVelocity = mCenterPosition + Vector3(rand() % 50,0, rand() % 50) - mPosition;
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::CAUTION, Motion::MOVE_MOTION);
	}
}

void Lizard::CautionProcess(float deltaTime)
{

	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis < 100)
	{
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::DISCOVERY, Motion::MOVE_MOTION);
	}

	mTimer += deltaTime;


	if (mTimer > 3)
	{
		mTimer = 0;
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}

	float dot = VDot(VNorm(mVelocity), Vector3(0, 0, 1));
	float rad = atan2(mVelocity.x, mVelocity.z);

	mVelocity = VNorm(mVelocity) * deltaTime;
	mPosition += mVelocity * 30;
	mRotate = MGetRotY(rad);
}

void Lizard::DiscoveryProcess(float deltaTime)
{
	if (mTarget)
	{
		Vector3 to_target = mTarget->GetPosition() - mPosition;
		Vector3 forward_cross_target = VCross(mRotate.GetForward(), to_target);
		float forward_dot_target = VDot(Vector3::Normalize(mRotate.GetForward()), to_target.Normalize());
		float up_dot_cross = VDot(mRotate.GetUp(), forward_cross_target);

		if (up_dot_cross >= 0.0f)
		{
			float angle = 1 * deltaTime;
			mRotate = mRotate * MGetRotY(angle);
		}
		else
		{
			float angle = -1 * deltaTime;
			mRotate = mRotate * MGetRotY(angle);
		}

		float dis = VSize(mTarget->GetPosition() - mPosition);
		mVelocity = mTarget->GetPosition() - mPosition;

		if (dis > 110)
		{
			mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
			StateChange(State::IDLE, Motion::IDLE_MOTION);
		}
		if (dis <= 110 && isFront(forward_dot_target))
		{
			mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
			StateChange(State::ATTACK, Motion::ATTACK_MOTION);
		}

		/*float dot = VDot(VNorm(mVelocity), Vector3(0, 0, 1));
		float rad = atan2(mVelocity.x, mVelocity.z);

		mVelocity = VNorm(mVelocity) * deltaTime;
		mPosition += mVelocity * 10;
		mRotate = MGetRotY(rad);*/
	}
}

void Lizard::AttackProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		Vector3 pos = mPosition + mRotate.GetForward() * 5 + Vector3(0, 12, 0);
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<FireBall>(mWorld, pos, VNorm(mVelocity), Tag::ENEMY_ATTACK, mAttackPower));
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Lizard::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		//mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void Lizard::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Lizard::Hit(float damage)
{
	SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
	mHitPoint -= damage;
	mHitEffect.Play();
	mHitEffect.SetPosition(mPosition + Vector3(0, 10, 0));
	if (mHitPoint <= 0)
	{
		mBody.isAlive = false;
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DEAD, Motion::DEAD_MOTION);
	}
	else
	{
		mAnimator.AnimationChange(Motion::DAMAGE_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DAMAGE, Motion::DAMAGE_MOTION);
	}
}

bool Lizard::isFront(float forward_dot_target)
{
	return (forward_dot_target >= 0.98f);
}
