#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Field/Field.h"
#include"PlayerAttack.h"
#include"../Magic/IceNeedle/IceNeedle.h"
#include"../Magic/FireBall/FireBall.h"
#include"../Magic/RockBlast/RockBlast.h"
#include"../Magic/FireWall/FireWall.h"
#include"../Magic/MagicMine/MagicMine.h"
#include"../Magic/BlackSpear/SpearCircle.h"
#include"../../Sound/SoundManager.h"
#include"../../AssetStorage/AssetStorage.h"
#include"../../System/PlayerStateSave/PlayerSave.h"
#include"../UI/TextDraw.h"

enum MotionID
{
	MOTION_IDLE = 0,
	MOTION_ATTACK = 1
};

Player::Player(IWorld* world, Vector3 position):
	Actor(world, "Player", position, {Line(position,position + Vector3(0,5,0)),2.0f },Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f),
	mAtk(20),
	mAtkBoost(0),
	mMagicInterval(3),
	mCurrentMagic(MagicList::FIREBALL),
	mPowerEX(0),
	mMagicEX(0),
	mNextPowerEX(3),
	mNextMagicEX(3)
{
	SetStatus(PlayerSave::getInstance().Load());
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Player"));
	mWeaponHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Sword"));
}

Player::Player(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Player", position,rotate,{ Line(position,position + Vector3(0,5,0)),2.0f },Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f),
	mAtk(20),
	mAtkBoost(0),
	mMagicInterval(3),
	mCurrentMagic(MagicList::FIREBALL),
	mPowerEX(0),
	mMagicEX(0),
	mNextPowerEX(3),
	mNextMagicEX(3)
{	 
	SetStatus(PlayerSave::getInstance().Load());
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Player"));
	mWeaponHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Sword"));
}

Player::~Player()
{
	PlayerStatus player;
	player.HP = mHitPoint;
	player.MaxHP = MAXHP;
	player.MP = mMagicPoint;
	player.MaxMP = MAXMP;
	player.AtkBoost = mAtkBoost;
	player.CurrentMagic = mCurrentMagic;
	player.List = mMagicList;
	PlayerSave::getInstance().Save(player);
}

float Player::GetHP()
{
	return mHitPoint;
}

float Player::GetMaxHp()
{
	return MAXHP;
}

float Player::GetMP()
{
	return mMagicPoint;
}

float Player::GetMaxMP()
{
	return MAXMP;
}

float Player::GetMagicInterval()
{
	return mMagicInterval;
}

float Player::GetAtk()
{
	return mAtk;
}

std::vector<MagicList> Player::GetHaveMagic()
{
	return mMagicList;
}

void Player::onStart()
{
	mRotate.SetScale({ 0.8f,0.8f,0.8f });
	mAnimator.Initialize(mModelHandle, 0,false);
}

void Player::onUpdate(float deltaTime)
{
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0,10,0), mPosition + Vector3(0,-30, 0), h))
	{
		mPosition.y = h.y;
	}

	StateUpdate(deltaTime);
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);

	MV1SetMatrix(mModelHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	Matrix S = MGetIdent();
	Matrix WeaponMatrix = S.SetScale(Vector3(5, 5, 5)) * MGetRotY(200 * DX_PI / 180) * MGetRotZ(30 * DX_PI / 180) * SetModelFramePosition(mModelHandle, "R_HandPinky1", mWeaponHandle);
	MV1SetMatrix(mWeaponHandle, WeaponMatrix);

	MagicCharge(deltaTime);
	ATKCharge(deltaTime);

	mAnimator.Update(deltaTime);

}

void Player::onDraw() const
{
	MV1DrawModel(mModelHandle);
}

void Player::onCollide(Actor & other)
{

}

void Player::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::PLAYER_DAMEGE:
		if (mState != State::DAMAGE)
		{
			float * damege = (float*)p;
			Hit(*damege);
		}
		break;

	case EventMessage::PLAYER_HEALING:
		mHitPoint = MAXHP;
		mMagicPoint = MAXMP;
		break;
	case EventMessage::MAGIC_GET:
	{
		MagicList* magic = (MagicList*)p;
		mMagicList.push_back(*magic);
	}
	break;
	case EventMessage::MAGIC_CHANGE:
	{
		MagicList* magic = (MagicList*)p;
		if (mCurrentMagic != *magic)
		{
			mCurrentMagic = *magic;
			mMagicInterval = 0;

		}
	}
		break;
	case  EventMessage::PLAYER_POWERUP: PowerUp(); break;
	case EventMessage::PLAYER_MAGICUP: MagicUp(); break;
	}
}

Matrix Player::SetModelFramePosition(int ModelHandle, char * FrameName, int SetModelHandle) const
{
	MATRIX FrameMatrix;
	int FrameIndex;
	FrameIndex = MV1SearchFrame(ModelHandle, FrameName);
	FrameMatrix = MV1GetFrameLocalWorldMatrix(ModelHandle, FrameIndex);
	return (Matrix)FrameMatrix;
}

void Player::StateChange(State state)
{
	mState = state;
	mStateTimer = 0.0f;
}

void Player::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case Player::MOVE: MoveProcess(deltaTime); break;
	case Player::ATTACK: AttackProcess(deltaTime); break;
	case Player::DAMAGE: DamegeProcess(deltaTime); break;
	}
	mStateTimer += deltaTime;
}

void Player::MoveProcess(float deltaTime)
{
	mVelocity = Vector3(0,0,0);
	mVelocity = VNorm(mRotate.GetForward()) * Input::getInstance().GetLeftAnalogStick().y * 60 * deltaTime;
	mVelocity += VNorm(mRotate.GetLeft()) * Input::getInstance().GetLeftAnalogStick().x * 60 * deltaTime;

	if (Input::getInstance().GetKeyDown(KEY_INPUT_RSHIFT) || Input::getInstance().GetKeyDown(ButtonCode::PAD_Button9))
	{
		mVelocity *= 2;
		mAtk = 0;
		mMagicInterval = 0;
	}

	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * deltaTime));
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);
	mPosition += mVelocity + Vector3(0, -0.1, 0);

	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_Z) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button1))
	{
		SoundManager::getInstance().Play("./res/Sound/PlayerAttack.mp3");
		StateChange(State::ATTACK);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<PlayerAttack>(mWorld, mWeaponHandle,mAtk + mAtkBoost));
		mAtk = 0;
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_X) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button4))
	{
		if (mMagicInterval >= 3)
		{
			MagicAttack();
		}
	}
}

void Player::AttackProcess(float deltaTime)
{
	mAnimator.AnimationChange(MotionID::MOTION_ATTACK, 1, 0.5f);
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(MotionID::MOTION_IDLE, 0);
		StateChange(State::MOVE);
	}
}

void Player::DamegeProcess(float deltaTime)
{
	auto backVelcity = mPosition + (-mRotate.GetForward() * 10);
	mPosition = Vector3::Lerp(mPosition, backVelcity, 0.1f);
	if (mStateTimer > 0.5f)
	{
		StateChange(State::MOVE);
	}
}

void Player::Hit(float damege)
{
	SoundManager::getInstance().Play("./res/Sound/PlayerDamage.ogg");
	StateChange(State::DAMAGE);
	mHitPoint -= damege;
}

void Player::ATKCharge(float deltaTime)
{
	mAtk += 20 / 3 * deltaTime;
	mAtk = min(mAtk, 20);
}

void Player::MagicCharge(float deltaTime)
{
	mMagicInterval += deltaTime;
	mMagicInterval = min(mMagicInterval, 3);
}

void Player::SetStatus(PlayerStatus status)
{
	MAXHP = status.MaxHP;
	MAXMP = status.MaxMP;
	mHitPoint = status.HP;
	mMagicPoint = status.MP;
	mAtkBoost = status.AtkBoost;
	mCurrentMagic = status.CurrentMagic;
	mMagicList = status.List;
}

void Player::MagicAttack()
{
	switch (mCurrentMagic)
	{

	case MagicList::FIREBALL:
	{
		if (mMagicPoint < 5) return;
		auto camera = mWorld->GetCamera();
		Vector3 icePos = mPosition + (camera->GetRotate().GetForward() * 20);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireBall>(mWorld, icePos, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK));
		mMagicPoint -= 5;
	}
	break;

	case MagicList::ICENEEDLE:
	{
		if (mMagicPoint < 15) return;
		Vector3 icePos = mPosition + (mRotate.GetForward() * 20);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld, icePos, mRotate.GetForward(), 3, Tag::PLAYER_ATTACK));
		mMagicPoint -= 15;
	}
	break;

	case MagicList::HEALING:
		if (mMagicPoint < 20 || mHitPoint >= MAXHP) return;
		mHitPoint = min(mHitPoint += 50, MAXHP);
		mMagicPoint -= 20;
		break;

	case MagicList::ROCKBLAST:
	{
		if (mMagicPoint < 20) return;
		auto camera = mWorld->GetCamera();
		Vector3 icePos = camera->GetPosition() + (camera->GetRotate().GetForward());
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<RockBlast>(mWorld, icePos, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK));
		mMagicPoint -= 20;
	}
	break;

	case MagicList::FIREWALL:
	{
		if (mMagicPoint < 18) return;
		auto camera = mWorld->GetCamera();
		Vector3 Pos = mPosition;
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireWall>(mWorld, Pos, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK));
		mMagicPoint -= 18;
	}
	break;

	case MagicList::MAGICMINE:
	{
		if (mMagicPoint < 30) return;
		auto camera = mWorld->GetCamera();
		Vector3 Pos = camera->GetPosition();
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<MagicMine>(mWorld, Pos, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK));
		mMagicPoint -= 30;
	}
	break;

	case MagicList::TRAPSPEAR:
	{
		if (mMagicPoint < 25) return;
		Vector3 Pos = mPosition + Vector3(0,1,0);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<SpearCircle>(mWorld, Pos, Tag::PLAYER_ATTACK));
		mMagicPoint -= 25;
	}
	break;

	}
	mMagicInterval = 0;
}

void Player::PowerUp()
{
	mPowerEX++;
	if (mPowerEX >= mNextPowerEX)
	{
		mWorld->AddActor(ActorGroup::Effect, std::make_shared<TextDraw>(mWorld, "ëÃóÕÇ™è„Ç™Ç¡ÇΩ"));
		MAXHP += 30;
		mAtkBoost += 5;
		MAXHP = min(MAXHP, 999);
		mNextPowerEX += 3;
	}
}

void Player::MagicUp()
{
	mMagicEX++;
	if (mMagicEX >= mNextMagicEX)
	{
		mWorld->AddActor(ActorGroup::Effect, std::make_shared<TextDraw>(mWorld, "ñÇóÕÇ™è„Ç™Ç¡ÇΩ"));
		MAXMP += 15;
		MAXMP = min(MAXMP, 999);
		mNextMagicEX += 15;
	}
}
