#include "Golem.h"
#include"GolemAttack.h"
#include"../../../Sound/SoundManager.h"

Golem::Golem(IWorld* world, Vector3 position):
	Actor(world, "Golem", position, { {0,10,0},3.0f }),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE)
{
	mHitPoint = 100;
	mModel = MV1LoadModel("./res/golem/golem.mv1");
}

void Golem::onStart()
{
	mRotate.SetScale({0.8f,0.8f,0.8f});
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
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	mBody.Translate(mPosition).Draw();
}

void Golem::onCollide(Actor & other)
{
	if (other.GetName() == "Attack" && mState != State::DAMAGE)
	{
		SoundManager::getInstance().Play("./res/Sound/PlayerAttack.ogg");
		if (mHitPoint <= 0)
		{
			SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
			mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
			StateChange(State::DEAD , Motion::DEAD_MOTION);
		}
		else
		{
			mHitPoint -= 50;
			mAnimator.AnimationChange(Motion::DAMAGE_MOTION, 0.3f, 0.5f, false);
			StateChange(State::DAMAGE, Motion::DAMAGE_MOTION);
		}
	}
}

void Golem::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: Idle(deltaTime); break;
	case State::MOVE: Move(deltaTime); break;
	case State::ATTACK: Attack(deltaTime); break;
	case State::DAMAGE: Damage(deltaTime); break;
	case State::DEAD: DeadState(deltaTime); break;
	}
}

void Golem::Idle(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis < 100)
	{
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::MOVE, Motion::MOVE_MOTION);
	}
}

void Golem::Move(float deltaTime)
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
			+ (mRotate.GetForward() * 10)
			+ Vector3(0, 20, 0)));
		mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
		StateChange(State::ATTACK, Motion::ATTACK_MOTION);
	}

	if (mTarget)
	{
		Vector3 velocity = mTarget->GetPosition() - mPosition;

		float dot = VDot(VNorm(velocity), Vector3(0,0,1));
		float rad = atan2(velocity.x,velocity.z);

		velocity = VNorm(velocity) * deltaTime;
		mPosition += velocity * 10;
		mRotate = MGetRotY(rad);
	}
}

void Golem::Attack(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Golem::DeadState(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		MV1DeleteModel(mModel);
		Dead();
	}
}

void Golem::Damage(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void Golem::StateChange(State nextState, Motion nextMotion)
{
	mState = nextState;
	mMotionid = nextMotion;
}
