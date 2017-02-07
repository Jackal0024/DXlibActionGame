#include "MagicStoneGolem.h"

#include"GolemAttack.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/AssetStorage.h"
#include"../../Gimmick/MagicStone.h"
#include"../../Magic/IceNeedle/IceNeedle.h"
#include"../../Magic/RockBlast/RockBlast.h"

MagicStoneGolem::MagicStoneGolem(IWorld* world, Vector3 position) :
	Actor(world, "MagicStoneGolem", position, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	isMagicAttack(true),
	mMagicType(MagicList::NONE)
{
	mHitPoint = 300;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("MagicStoneGolem"));
}

MagicStoneGolem::MagicStoneGolem(IWorld * world, Vector3 position, Vector3 rotate,MagicList type) :
	Actor(world, "MagicStoneGolem", position, rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mMotionid(Motion::IDLE_MOTION),
	mState(State::IDLE),
	isMagicAttack(true),
	mMagicType(type)
{
	mHitPoint = 300;
	mModel = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("MagicStoneGolem"));
}

MagicStoneGolem::~MagicStoneGolem()
{
	MV1DeleteModel(mModel);
}

void MagicStoneGolem::onStart()
{
	mAnimator.Initialize(mModel, mMotionid, true);

}

void MagicStoneGolem::onUpdate(float deltaTime)
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

void MagicStoneGolem::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose().SetScale(Vector3(1.2f,1.2f,1.2f))));
	MV1DrawModel(mModel);
	//mBody.Translate(mPosition).Draw();
}

void MagicStoneGolem::onCollide(Actor & other)
{


}

void MagicStoneGolem::onMessage(EventMessage message, void * p)
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

void MagicStoneGolem::StateUpdate(float deltaTime)
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

void MagicStoneGolem::IdleProcess(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis < 50 && isMagicAttack)
	{
		isMagicAttack = false;
		Vector3 icePos = mPosition + (mRotate.GetForward() * 20);
		if (mMagicType == MagicList::ICENEEDLE)
		{
			mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<IceNeedle>(mWorld, icePos, mRotate.GetForward(), 3, Tag::ENEMY_ATTACK));
		}
		if (mMagicType == MagicList::ROCKBLAST)
		{
			mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<RockBlast>(mWorld, mPosition + Vector3(0,5,0), mRotate.GetForward(),Tag::ENEMY_ATTACK));
		}
		mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
		StateChange(State::ATTACK, Motion::ATTACK_MOTION);
		return;
	}
	if (dis < 100)
	{
		mAnimator.AnimationChange(Motion::MOVE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::MOVE, Motion::MOVE_MOTION);
	}
}

void MagicStoneGolem::MoveProcess(float deltaTime)
{
	float dis = VSize(mTarget->GetPosition() - mPosition);
	if (dis > 100)
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
	if (dis < 10)
	{
		isMagicAttack = true;
		mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<EnemyArrack>(mWorld, mPosition
			+ (mRotate.GetForward() * 10)
			+ Vector3(0, 20, 0),
			mRotate.GetForward()));
		mAnimator.AnimationChange(Motion::ATTACK_MOTION, 0.3f, 0.5f, false);
		StateChange(State::ATTACK, Motion::ATTACK_MOTION);
	}

	if (mTarget)
	{
		Vector3 velocity = mTarget->GetPosition() - mPosition;

		float dot = VDot(VNorm(velocity), Vector3(0, 0, 1));
		float rad = atan2(velocity.x, velocity.z);

		velocity = VNorm(velocity) * deltaTime;
		mPosition += velocity * 15;
		mRotate = MGetRotY(rad);
	}
}

void MagicStoneGolem::AttackProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

void MagicStoneGolem::DeadProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mWorld->SendMsg(EventMessage::PLAYER_POWERUP);
		MV1DeleteModel(mModel);
		Dead();
	}
}

void MagicStoneGolem::DamageProcess(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(Motion::IDLE_MOTION, 0.3f, 0.5f, true);
		StateChange(State::IDLE, Motion::IDLE_MOTION);
	}
}

bool MagicStoneGolem::isFront(float forward_dot_target)
{
	return (forward_dot_target >= 0.98f);
}

void MagicStoneGolem::Hit(float damage)
{
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		mBody.isAlive = false;
		Vector3 pos = mPosition + Vector3(0, 10, 0);
		if (mMagicType == MagicList::ICENEEDLE) mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld, "アイスニードル", pos, MagicList::ICENEEDLE));
		if (mMagicType == MagicList::ROCKBLAST) mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld, "ロックブラスト", pos, MagicList::ROCKBLAST));
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

void MagicStoneGolem::StateChange(State nextState, Motion nextMotion)
{
	mState = nextState;
	mMotionid = nextMotion;
}
