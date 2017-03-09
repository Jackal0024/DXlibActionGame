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
#include"../UI/DeadEffect/DeadEffect.h"
#include"../UI/FlashEffect.h"

enum MotionID
{
	MOTION_IDLE = 0,
	MOTION_ATTACK = 1
};

Player::Player(IWorld* world, Vector3 position):
	Actor(world, "Player", position, {Line(position,position + Vector3(0,30,0)),10.0f },Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f),
	mStamina(100),
	mAttackPower(20),
	mMagicPower(20),
	mMagicInterval(1),
	mCurrentMagic(MagicList::NONE),
	mPowerEX(0),
	mMagicEX(0),
	mNextPowerEX(15),
	mNextMagicEX(10),
	mSpeed(1)
{
	SetStatus(PlayerSave::getInstance().Load());
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Player"));
	mWeaponHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Sword"));
}

Player::Player(IWorld * world, Vector3 position, Vector3 rotate) :
	Actor(world, "Player", position, rotate, { Line(position,position + Vector3(0,15,0)),2.0f }, Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f),
	mStamina(100),
	mAttackPower(20),
	mMagicPower(20),
	mMagicInterval(1),
	mCurrentMagic(MagicList::NONE),
	mPowerEX(0),
	mMagicEX(0),
	mNextPowerEX(15),
	mNextMagicEX(10),
	mSpeed(1)
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
	player.Stamina = mStamina;
	player.MaxStamina = MAXStamina;
	player.AtkBoost = mAttackPower;
	player.MagicBoost = mMagicPower;
	player.CurrentMagic = mCurrentMagic;
	player.List = mMagicList;
	PlayerSave::getInstance().Save(player);

	MV1DeleteModel(mModelHandle);
	MV1DeleteModel(mWeaponHandle);
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

float Player::GetStamina()
{
	return mStamina;
}

float Player::GetMaxStamina()
{
	return MAXStamina;
}

MagicList Player::GetCurrentMagic()
{
	return mCurrentMagic;
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

	mAnimator.Update(deltaTime);

}

void Player::onDraw() const
{
	//DrawFormatString(0, 300, GetColor(255, 255, 255), "X = %f : Y = %f : Z = %f", mPosition.x,mPosition.y, mPosition.z);
	MV1DrawModel(mModelHandle);
	//デバッグ表示
	//mBody.Move(mPosition).Draw();

}

void Player::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::ENEMY && !(mState == State::DAMAGE || mState == State::DEAD))
	{
		Vector3 pos = VNorm(mPosition - other.GetPosition());
		Hitinfo hit = { pos,10 };
		Hit(hit);
	}
}

void Player::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::PLAYER_DAMEGE:
		if (mState != State::DAMAGE && mState != State::DEAD)
		{
			Hitinfo* hit = (Hitinfo*)p;
			Hit(*hit);
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
	case Player::DEAD:   DeadProcess(deltaTime); break;
	}
}

void Player::MoveProcess(float deltaTime)
{
	mSpeed = 1.0f;
	mVelocity = Vector3(0,0,0);
	mVelocity = VNorm(mRotate.GetForward()) * Input::getInstance().GetLeftAnalogStick().y * deltaTime;
	mVelocity += VNorm(mRotate.GetLeft()) * Input::getInstance().GetLeftAnalogStick().x * deltaTime;

	if (Input::getInstance().GetKeyDown(KEY_INPUT_RSHIFT) || Input::getInstance().GetKeyDown(ButtonCode::PAD_Button8))
	{
		if (mStamina > 0)
		{
			mSpeed = 2.0f;
			mStamina -= 0.3f * (60 * deltaTime);
			mStamina = max(0, mStamina);
			mMagicInterval = 0;
		}
	}
	else
	{
		StaminaCharge(deltaTime);
	}

	float rotateSpeed = 2;
	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * (rotateSpeed * deltaTime)));
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);
	mPosition += (mVelocity.Normalize() * mSpeed) + Vector3(0, -0.1, 0);

	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_Z) || Input::getInstance().GetKeyDown(ButtonCode::PAD_Button4))
	{
		if (mStamina >= 40)
		{
			SoundManager::getInstance().Play("./res/Sound/PlayerAttack.mp3");
			StateChange(State::ATTACK);
			mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<PlayerAttack>(mWorld, mWeaponHandle, mAttackPower));
			mStamina -= 40;
		}
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_X) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button3))
	{
		if (mMagicInterval >= 0.5f)
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
	StaminaCharge(deltaTime);
	mStateTimer += deltaTime;
	auto backVelcity = mPosition + (mKnockBack * 10);
	mPosition = Vector3::Lerp(mPosition, backVelcity, 0.1f);
	if (mStateTimer > 0.5f)
	{
		StateChange(State::MOVE);
	}
}

void Player::DeadProcess(float deltaTime)
{
	StaminaCharge(deltaTime);
	mStateTimer += deltaTime * 80;
	MV1DeleteModel(mModelHandle);
	if (mStateTimer < 120) {
		mRotate = mRotate * MGetRotX(-1 * (DX_PI / 180));
	}
}

void Player::Hit(Hitinfo hit)
{
	SoundManager::getInstance().Play("./res/Sound/PlayerDamage.ogg");
	mHitPoint -= hit.damage;
	hit.position.y = 0;
	mKnockBack = VNorm(hit.position);
	mHitPoint = max(0, mHitPoint);
	if (mHitPoint <= 0)
	{
		SoundManager::getInstance().Play("./res/Sound/PlayerDead.mp3");
		mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<DeadEffect>(mWorld));
		StateChange(State::DEAD);
	}
	else
	{
		mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<FlashEffect>(mWorld, 125, 0.3f, GetColor(255, 0, 0)));
		StateChange(State::DAMAGE);
	}
}

void Player::StaminaCharge(float deltaTime)
{
	mStamina += 0.5f * (60 * deltaTime);
	mStamina = min(mStamina, MAXStamina);
}

void Player::MagicCharge(float deltaTime)
{
	mMagicInterval += deltaTime;
	mMagicInterval = min(mMagicInterval, 1);
}

void Player::SetStatus(PlayerStatus status)
{
	MAXHP = status.MaxHP;
	MAXMP = status.MaxMP;
	MAXStamina = status.MaxStamina;
	if (status.HP == 0)
	{
		mHitPoint = MAXHP;
		mMagicPoint = MAXMP;
		mStamina = MAXStamina;
	}
	else
	{
		mHitPoint = status.HP;
		mMagicPoint = status.MP;
		mStamina = status.Stamina;
	}
	mAttackPower = status.AtkBoost;
	mMagicPower = status.MagicBoost;
	mCurrentMagic = status.CurrentMagic;
	mMagicList = status.List;
}

void Player::MagicAttack()
{
	switch (mCurrentMagic)
	{
	case MagicList::FIREBALL:FireBallInvoke(); break;
	case MagicList::ICENEEDLE:IceNeedleInvoke(); break;
	case MagicList::HEALING:HealingInvoke(); break;
	case MagicList::ROCKBLAST: RockBlastInvoke(); break;
	case MagicList::FIREWALL: FireWallInvoke(); break;
	case MagicList::MAGICMINE: MagicMineInvoke(); break;
	case MagicList::TRAPSPEAR: TrapSpearInvoke();  break;
	}
	mMagicInterval = 0;
}

void Player::PowerUp()
{
	mPowerEX++;
	if (mPowerEX >= mNextPowerEX)
	{
		SoundManager::getInstance().Play("./res/Sound/PowerUp.mp3");
		mWorld->AddActor(ActorGroup::Effect, std::make_shared<TextDraw>(mWorld, "体力が上がった"));
		MAXHP += 4;
		MAXStamina += 4;
		mAttackPower += 2;
		MAXStamina = min(MAXStamina, 600);
		MAXHP = min(MAXHP, 600);
		mNextPowerEX += 15;
	}
}

void Player::MagicUp()
{
	mMagicEX++;
	if (mMagicEX >= mNextMagicEX)
	{
		SoundManager::getInstance().Play("./res/Sound/MagicUp.mp3");
		mWorld->AddActor(ActorGroup::Effect, std::make_shared<TextDraw>(mWorld, "魔力が上がった"));
		MAXMP += 15;
		mMagicPower += 2;
		MAXMP = min(MAXMP, 600);
		mNextMagicEX += 10;
	}
}


//魔法攻撃各種-------------------------------------------------------------------
void Player::FireBallInvoke()
{
	const float MPCOST = 5;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = mPosition + (camera->GetRotate().GetForward()) + Vector3(0, 11, 0);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireBall>(mWorld, createPosition, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::IceNeedleInvoke()
{
	const float MPCOST = 15;

	if (mMagicPoint < MPCOST) return;
	Vector3 createPosition = mPosition + (mRotate.GetForward() * 20);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld, createPosition, mRotate.GetForward(), 3, Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::HealingInvoke()
{
	const float MPCOST = 20;

	if (mMagicPoint < MPCOST || mHitPoint >= MAXHP) return;
	SoundManager::getInstance().Play("./res/Sound/PlayerHeal.mp3");
	mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<FlashEffect>(mWorld, 125, 0.3f, GetColor(0, 255, 65)));
	mHitPoint = min(mHitPoint += 50, MAXHP);
	mMagicPoint -= MPCOST;
}

void Player::RockBlastInvoke()
{
	const float MPCOST = 10;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = camera->GetPosition() + (camera->GetRotate().GetForward()) + Vector3(0, 3, 0);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<RockBlast>(mWorld, createPosition, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::FireWallInvoke()
{
	const float MPCOST = 18;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = mPosition;
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireWall>(mWorld, createPosition, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::MagicMineInvoke()
{
	const float MPCOST = 30;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = camera->GetPosition();
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<MagicMine>(mWorld, createPosition, camera->GetRotate().GetForward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::TrapSpearInvoke()
{
	const float MPCOST = 25;

	if (mMagicPoint < MPCOST) return;
	Vector3 createPosition = mPosition + Vector3(0, 1, 0);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<SpearCircle>(mWorld, createPosition, Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

//------------------------------------------------------------------------------------------
