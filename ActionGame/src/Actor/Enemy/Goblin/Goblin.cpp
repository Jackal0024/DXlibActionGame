#include "Goblin.h"
#include"GoblinAttack.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"

Goblin::Goblin(IWorld * world, Vector3 position):
	Actor(world, "Goblin", position, { { 0,10,0 },4.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mCenterPoint(position)
{
	mHitPoint = 200;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Goblin"));
}

Goblin::Goblin(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Goblin", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mCenterPoint(position)
{
	mHitPoint = 200;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Goblin"));
}

Goblin::~Goblin()
{
}

void Goblin::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);
}

void Goblin::onUpdate(float deltaTime)
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

void Goblin::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void Goblin::onCollide(Actor & other)
{

}

void Goblin::onMessage(EventMessage message, void * p)
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

void Goblin::StateUpdate(float deltaTime)
{
	if (!mTarget) IdleProcess(deltaTime);

	switch (mState)
	{
	case State::IDLE: IdleProcess(deltaTime); break;
	case State::MOVE : MoveProcess(deltaTime); break;
	case State::LIGHT_ATTACK: LightAttackProcess(deltaTime); break;
	case State::HEAVY_ATTACK: HeavyAttackProcess(deltaTime); break;
	case State::DAMAGE: DamageProcess(deltaTime); break;
	case State::DEAD: DeadProcess(deltaTime); break;
	}
}

void Goblin::StateChange(State nextState, Motion nextMotion)
{
	if (mState == nextState) return;
	mState = nextState;
	mMotionid = nextMotion;
}

void Goblin::IdleProcess(float deltaTime)
{
	mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
	Vector3 subVec = mTarget->GetPosition() - mPosition;
	if (VSize(subVec) <= 200)
	{
		StateChange(State::MOVE);
	}

}

void Goblin::MoveProcess(float deltaTime)
{
	Vector3 subVec = mTarget->GetPosition() - mPosition;
	if (VSize(subVec) <= 30)
	{
		mAnimator.AnimationChange(Motion::WALK_MOTION , 0.3f, 0.5f, true);
		float dot = VDot(VNorm(subVec), Vector3(0, 0, 1));
		float rad = atan2(subVec.x, subVec.z);

		Vector3 velocity = VNorm(subVec) * deltaTime;
		mPosition += velocity * 10;
		mRotate = MGetRotY(rad);
		if (VSize(subVec) <= 10)
		{
			//UŒ‚
			mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<GoblinAttack>(mWorld, mPosition
				+ (mRotate.GetForward() * 10), 0.4f));
			StateChange(State::LIGHT_ATTACK);
		}
	}
	else if (VSize(subVec) <= 200)
	{
		mAnimator.AnimationChange(Motion::RUN_MOTION, 0.3f, 0.5f, true);

		float dot = VDot(VNorm(subVec), Vector3(0, 0, 1));
		float rad = atan2(subVec.x, subVec.z);

		Vector3 velocity = VNorm(subVec) * deltaTime;
		mPosition += velocity * 50;
		mRotate = MGetRotY(rad);
	}
	else if(VSize(subVec) >= 200)
	{
		Vector3 backVec = mCenterPoint - mPosition;
		mAnimator.AnimationChange(Motion::WALK_MOTION, 0.3f, 0.5f, true);
		float dot = VDot(VNorm(backVec), Vector3(0, 0, 1));
		float rad = atan2(backVec.x, backVec.z);

		Vector3 velocity = VNorm(backVec) * deltaTime;
		mPosition += velocity * 10;
		mRotate = MGetRotY(rad);
		if (VSize(backVec) <= 5)
		{
			StateChange(State::IDLE);
		}
	}
}

void Goblin::HeavyAttackProcess(float deltaTime)
{
	mAnimator.AnimationChange(Motion::HEAVY_ATTACK_MOTION, 0.3f, 0.5f, false);
	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Goblin::LightAttackProcess(float deltaTime)
{
	mAnimator.AnimationChange(Motion::LIGHT_ATTACK_MOTION, 0.3f, 0.5f, false);
	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Goblin::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void Goblin::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Goblin::Hit(float damage)
{
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DEAD, Motion::DEAD_MOTION);
	}
	else
	{
		mAnimator.AnimationChange(Motion::DAMAGE_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DAMAGE, Motion::DAMAGE_MOTION);
	}
}
