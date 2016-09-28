#include "Lizard.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../Magic/FireBall/FireBall.h"

Lizard::Lizard(IWorld * world, Vector3 position):
Actor(world, "Lizard", position, { { 0,10,0 },3.0f }, Tag::ENEMY),
mMotionid(Motion::IDLE_MOTION),
mState(State::IDLE),
mCenterPosition(position),
mTimer(0)
{
	mHitPoint = 100;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Lizard"));
}

Lizard::Lizard(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Lizard", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mCenterPosition(position),
	mTimer(0)
{
	mHitPoint = 100;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Lizard"));
}

Lizard::~Lizard()
{
}

void Lizard::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);
}

void Lizard::onUpdate(float deltaTime)
{
	mPosition += Vector3(0, -0.1, 0);
	mTarget = mWorld->FindActor("Player");

	StateUpdate(deltaTime);
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);

	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}

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
	float dis = VSize(mTarget->GetPosition() - mPosition);
	mVelocity = mTarget->GetPosition() - mPosition;

	if (dis > 110)
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
	if (dis < 50)
	{
		mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
		StateChange(State::ATTACK, Motion::ATTACK_MOTION);
	}
	if (mTarget)
	{
		float dot = VDot(VNorm(mVelocity), Vector3(0, 0, 1));
		float rad = atan2(mVelocity.x, mVelocity.z);

		mVelocity = VNorm(mVelocity) * deltaTime;
		mPosition += mVelocity * 10;
		mRotate = MGetRotY(rad);
	}
}

void Lizard::AttackProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<FireBall>(mWorld, mPosition, VNorm(mVelocity), Tag::PLAYER_ATTACK));
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Lizard::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
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
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DEAD, Motion::DEAD_MOTION);
	}
	else
	{
		mAnimator.AnimationChange(Motion::DAMAGE_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DAMAGE, Motion::DAMAGE_MOTION);
	}
}
