#include "MagicMommy.h"
#include"MummyAttack.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../Magic/MagicMine/MagicMine.h"
#include"../../Gimmick/MagicStone.h"

MagicMummy::MagicMummy(IWorld * world, Vector3 position) :
	Actor(world, "MagicMummy", position, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStateTimer(0.0f),
	mStateBool(false)
{
	mHitPoint = 200;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("MagicMummy"));
}

MagicMummy::MagicMummy(IWorld * world, Vector3 position, Vector3 rotate) :
	Actor(world, "MagicMummy", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	mStateTimer(0.0f),
	mStateBool(false)
{
	mHitPoint = 200;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("MagicMummy"));
}

void MagicMummy::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);
	PartnerSearch();
}

void MagicMummy::onUpdate(float deltaTime)
{
	mTarget = mWorld->FindActor("Player");

	StateUpdate(deltaTime);

	mAnimator.Update(deltaTime);
}

void MagicMummy::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void MagicMummy::onCollide(Actor & other)
{
}

void MagicMummy::onMessage(EventMessage message, void * p)
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

void MagicMummy::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: IdleProcess(deltaTime); break;
	case State::MOVE: MoveProcess(deltaTime); break;
	case State::MAGIC: MagicProcess(deltaTime); break;
	case State::KICK: KickProcess(deltaTime); break;
	case State::DAMAGE: DamageProcess(deltaTime); break;
	case State::DEAD: DeadProcess(deltaTime); break;
	}
	mStateTimer += deltaTime;
}

void MagicMummy::StateChange(State nextState, Motion nextMotion)
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
void MagicMummy::IdleProcess(float deltaTime)
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

void MagicMummy::MoveProcess(float deltaTime)
{
	if (mPartner)
	{
		Vector3 partnersub = mPartner->GetPosition() - mPosition;

		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		float dot = VDot(VNorm(partnersub), Vector3(0, 0, 1));
		float rad = atan2(partnersub.x, partnersub.z);

		Vector3 velocity = VNorm(partnersub) * deltaTime;
		mPosition += velocity * VSize(partnersub);
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

void MagicMummy::MagicProcess(float deltaTime)
{
	Vector3 targetsub = mTarget->GetPosition() - mPosition;

	mAnimator.AnimationChange(Motion::MAGIC_MOTION, 0.3f, 0.5f, false);

	float dot = VDot(VNorm(targetsub), Vector3(0, 0, 1));
	float rad = atan2(targetsub.x, targetsub.z);
	mRotate = MGetRotY(rad);

	if (mStateTimer > 1.0f && !mStateBool)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<MagicMine>(mWorld, mPosition, VNorm(targetsub), Tag::ENEMY_ATTACK));
		mStateBool = true;
	}

	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void MagicMummy::KickProcess(float deltaTime)
{
	Vector3 targetsub = mTarget->GetPosition() - mPosition;

	mAnimator.AnimationChange(Motion::KICK_MOTION, 0.3f, 0.5f, false);

	float dot = VDot(VNorm(targetsub), Vector3(0, 0, 1));
	float rad = atan2(targetsub.x, targetsub.z);

	mRotate = MGetRotY(rad);

	//攻撃
	if (mStateTimer > 0.3f && !mStateBool)
	{
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<MummyAttack>(mWorld, mPosition
			+ (mRotate.GetForward() * 10)));
	}

	if (mAnimator.IsAnimationEnd())
	{
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void MagicMummy::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void MagicMummy::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void MagicMummy::Hit(float damage)
{
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		SoundManager::getInstance().Play("./res/Sound/EnemyVoice.ogg");
		mAnimator.AnimationChange(Motion::DEAD_MOTION, 0.3f, 0.5f, false);
		Vector3 pos = mPosition + Vector3(0, 10, 0);
		mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld, "マジックマイン", pos, MagicList::MAGICMINE));
		StateChange(State::DEAD, Motion::DEAD_MOTION);

	}
	else
	{
		mAnimator.AnimationChange(Motion::MIN_DAMAGE_MOTION, 0.3f, 0.5f, false);
		StateChange(State::DAMAGE, Motion::MIN_DAMAGE_MOTION);
	}
}

void MagicMummy::PartnerSearch()
{
	if (mWorld->FindActor("Goblin"))
	{
		mPartner = mWorld->FindActor("Goblin");
	}
	else
	{
		mPartner = nullptr;
	}
}
