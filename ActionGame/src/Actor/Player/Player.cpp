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
	//プレイヤーのステータスをロード
	SetStatus(PlayerSave::getInstance().Load());
	//プレイヤーモデルの複製
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Player"));
	//剣モデルの複製
	mWeaponHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Sword"));
}

Player::Player(IWorld * world, Vector3 position, Vector3 rotate) :
	Actor(world, "Player", position + Vector3(0,10,0), rotate, { Line(position,position + Vector3(0,15,0)),2.0f }, Tag::PLAYER),
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
	//プレイヤーのステータスをロード
	SetStatus(PlayerSave::getInstance().Load());
	//プレイヤーモデルの複製
	mModelHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Player"));
	//剣モデルの複製
	mWeaponHandle = MV1DuplicateModel(AssetStorage::getInstance().GetHandle("Sword"));
}

Player::~Player()
{
	//プレイヤーのステートをセーブ--------------
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
	//------------------------------------------
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
	mRotate.Scale({ 0.8f,0.8f,0.8f });
	mAnimator.Initialize(mModelHandle, 0,false);
}

void Player::onUpdate(float deltaTime)
{
	//プレイヤーが地面に接地する処理----------------------------------------------------------------
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0,10,0), mPosition + Vector3(0,-30, 0), h))
	{
		mPosition.y = h.y;
	}
	//-----------------------------------------------------------------------------------------------

	StateUpdate(deltaTime);
	//壁との接触判定
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);

	//表示のための計算--------------------------------------------------------------------------------------
	Matrix S = Matrix::Identity;
	Matrix WeaponMatrix = S.Scale(Vector3(5, 5, 5)) * Matrix::CreateRotationY(200) * Matrix::CreateRotationZ(30) * SetModelFramePosition(mModelHandle, "R_HandPinky1", mWeaponHandle);
	MV1SetMatrix(mWeaponHandle, WeaponMatrix);
	//------------------------------------------------------------------------------------------------------

	MagicCharge(deltaTime);

	mAnimator.Update(deltaTime);

}

void Player::onDraw() const
{
	//モデルデータが前後ろ逆なため描画時１８０度回転する
	MV1SetMatrix(mModelHandle, Matrix::CreateRotationY(180) * GetPose());
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

//剣のモデルを手にくっ付ける処理
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
	//スティックによって操作する-----------------------------------------------------------------------
	mVelocity = Vector3(0,0,0);
	mVelocity =  VNorm(mRotate.Forward()) * Input::getInstance().GetLeftAnalogStick().y * deltaTime;
	mVelocity += VNorm(mRotate.Left()) * Input::getInstance().GetLeftAnalogStick().x * deltaTime;
	//-------------------------------------------------------------------------------------------------

	//ダッシュボタンが押されたら
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

	//右スティックでプレイヤーを回転させる-------------------------------------------------------------------------
	float rotateSpeed = 2;
	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * (rotateSpeed * deltaTime)));
	//-------------------------------------------------------------------------------------------------------------
	//移動時壁にめり込まないように計算
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius, mVelocity);
	//重力処理
	mPosition += (mVelocity.Normalize() * mSpeed) + Vector3(0.f, -0.1f, 0.f);

	//攻撃ボタンが押されたら攻撃
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
	//魔法攻撃ボタンで魔法攻撃
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_X) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button3))
	{
		if (mMagicInterval >= 0.5f)
		{
			MagicAttack();
		}
	}
}

//攻撃のアニメーション処理
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
	//ノックバック処理----------------------------------------------
	auto backVelcity = mPosition + (mKnockBack * 10);
	mPosition = Vector3::Lerp(mPosition, backVelcity, 0.1f);
	//--------------------------------------------------------------
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
		//回転しながら死亡する
		mRotate = mRotate * Matrix::CreateRotationX(-1);
	}
}

//ヒット時の処理
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
		mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<FlashEffect>(mWorld, 125.f, 0.3f, GetColor(255, 0, 0)));
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
	Vector3 createPosition = mPosition + (camera->GetRotate().Forward()) + Vector3(0, 11, 0);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireBall>(mWorld, createPosition, camera->GetRotate().Forward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::IceNeedleInvoke()
{
	const float MPCOST = 15;

	if (mMagicPoint < MPCOST) return;
	Vector3 createPosition = mPosition + (mRotate.Forward() * 20.f);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld, createPosition, mRotate.Forward(), 3, Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::HealingInvoke()
{
	const float MPCOST = 20;

	if (mMagicPoint < MPCOST || mHitPoint >= MAXHP) return;
	SoundManager::getInstance().Play("./res/Sound/PlayerHeal.mp3");
	mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<FlashEffect>(mWorld, 125.0f, 0.3f, GetColor(0, 255, 65)));
	mHitPoint = min(mHitPoint += 50, MAXHP);
	mMagicPoint -= MPCOST;
}

void Player::RockBlastInvoke()
{
	const float MPCOST = 10;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = camera->GetPosition() + (camera->GetRotate().Forward()) + Vector3(0, 3, 0);
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<RockBlast>(mWorld, createPosition, camera->GetRotate().Forward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::FireWallInvoke()
{
	const float MPCOST = 18;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = mPosition;
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<FireWall>(mWorld, createPosition, camera->GetRotate().Forward(), Tag::PLAYER_ATTACK, mMagicPower));
	mMagicPoint -= MPCOST;
}

void Player::MagicMineInvoke()
{
	const float MPCOST = 30;

	if (mMagicPoint < MPCOST) return;
	auto camera = mWorld->GetCamera();
	Vector3 createPosition = camera->GetPosition();
	mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<MagicMine>(mWorld, createPosition, camera->GetRotate().Forward(), Tag::PLAYER_ATTACK, mMagicPower));
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
