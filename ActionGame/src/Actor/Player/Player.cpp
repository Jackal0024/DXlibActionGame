#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Field/Field.h"
#include"PlayerAttack.h"
#include"../Magic/IceNeedle/IceNeedle.h"
#include"../../Sound/SoundManager.h"

enum MotionID
{
	MOTION_IDLE = 0,
	MOTION_ATTACK = 1
};

Player::Player(IWorld* world, Vector3 position):
	Actor(world, "Player", position, {Line(position,position + Vector3(0,5,0)),2.0f },Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f)
{
	mHitPoint = MAXHP;
	mMagicPoint = MAXMP;
	mModelHandle = MV1LoadModel("./res/overload/overlord_Arm.mv1");
	mWeaponHandle = MV1LoadModel("./res/Rusted Longsword/LS.x");
}

Player::Player(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Player", position,rotate,{ Line(position,position + Vector3(0,5,0)),2.0f },Tag::PLAYER),
	mState(State::MOVE),
	mStateTimer(0.0f)
{
	mHitPoint = MAXHP;
	mMagicPoint = MAXMP;
	mModelHandle = MV1LoadModel("./res/overload/overlord_Arm.mv1");
	mWeaponHandle = MV1LoadModel("./res/Rusted Longsword/LS.x");
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

void Player::HPCalc(float value)
{
	mHitPoint += value;
}

void Player::onStart()
{
	mRotate.SetScale({ 0.8f,0.8f,0.8f });
	mAnimator.Initialize(mModelHandle, 0,false);
}

void Player::onUpdate(float deltaTime)
{
	Vector3 h;
	//mWorld->GetField().Collision(mPosition, mPosition + Vector3(0,3,0), mBody.mRadius);
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

	mTag;

	mAnimator.Update(deltaTime);

}

void Player::onDraw() const
{
	MV1DrawModel(mModelHandle);
}

void Player::onCollide(Actor & other)
{
	if (mState != State::DAMAGE)
	{
		SoundManager::getInstance().Play("./res/Sound/PlayerDamage.ogg");
		StateChange(State::DAMAGE);
	}
}

void Player::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::PLAYER_DAMEGE:
		if (mState != State::DAMAGE)
		{
			float * damege = (float*)p;
			HPCalc(-(*damege));
		}
		break;
	}
}

Matrix Player::SetModelFramePosition(int ModelHandle, char * FrameName, int SetModelHandle) const
{
	MATRIX FrameMatrix;
	int FrameIndex;
	// フレーム名からフレーム番号を取得する
	FrameIndex = MV1SearchFrame(ModelHandle, FrameName);
	// フレームの現在のワールドでの状態を示す行列を取得する
	FrameMatrix = MV1GetFrameLocalWorldMatrix(ModelHandle, FrameIndex);
	// セットするモデルの状態を示す行列をフレームの状態を示す行列と同じにする
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
	case Player::MOVE: Move(deltaTime); break;
	case Player::ATTACK: Attack(deltaTime); break;
	case Player::DAMAGE: Damege(deltaTime); break;
	}
	mStateTimer += deltaTime;
}

void Player::Move(float deltaTime)
{
	mVelocity = Vector3(0,0,0);
	mVelocity = mRotate.GetForward() * Input::getInstance().GetLeftAnalogStick().y * 60 * deltaTime;
	mVelocity += mRotate.GetLeft() * Input::getInstance().GetLeftAnalogStick().x * 60 * deltaTime;
	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * deltaTime));
	mPosition += mVelocity + Vector3(0, -0.1, 0);

	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_Z) || Input::getInstance().GetKeyDown(ButtonCode::PAD_Button1))
	{
		mWorld->SendMsg(EventMessage::DEAD);
		StateChange(State::ATTACK);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<PlayerAttack>(mWorld, mWeaponHandle));
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_X) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button4))
	{
		if (mMagicPoint >= 20)
		{
			Vector3 icePos = mPosition + (mRotate.GetForward() * 20);
			mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld, icePos, mRotate.GetForward(), 3));
			mMagicPoint -= 20;
		}
	}
	mMagicPoint += 0.02f;
	mMagicPoint = max(min(mMagicPoint, 100), 0);
}

void Player::Attack(float deltaTime)
{
	mAnimator.AnimationChange(MotionID::MOTION_ATTACK, 1, 0.5f);
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(MotionID::MOTION_IDLE, 0);
		StateChange(State::MOVE);
	}
}

void Player::Damege(float deltaTime)
{
	auto backVelcity = mPosition + (-mRotate.GetForward() * 10);
	mPosition = Vector3::Lerp(mPosition, backVelcity, 0.1f);
	if (mStateTimer > 0.5f)
	{
		StateChange(State::MOVE);
	}
}
