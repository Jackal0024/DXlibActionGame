#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Field/Field.h"
#include"PlayerAttack.h"

Player::Player(IWorld* world, Vector3 position):
	Actor(world, "Player", position, {Line(position,position + Vector3(0,5,0)),1.0f })
{
	mModelHandle = MV1LoadModel("./res/overload/overlord_Arm.mv1");
	mWeaponHandle = MV1LoadModel("./res/Rusted Longsword/LS.x");
}

void Player::onStart()
{
	mRotate.SetScale({ 0.8f,0.8f,0.8f });
	mAnimator.Initialize(mModelHandle, 0,false);
}

void Player::onUpdate(float deltaTime)
{
	

	Vector3 velocity;
	velocity = mRotate.GetForward() * Input::getInstance().GetLeftAnalogStick().y * 60 * deltaTime;
	velocity += mRotate.GetLeft() * Input::getInstance().GetLeftAnalogStick().x* 60 * deltaTime;
	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * deltaTime));
	mPosition += velocity + Vector3(0,-0.1,0);

	Vector3 h;
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0,3,0), mBody.mRadius);
	if (mWorld->GetField().Collision(mPosition + Vector3(0,10,0), mPosition + Vector3(0,-30, 0), h))
	{
		mPosition.y = h.y;
	}

	MV1SetMatrix(mModelHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	Matrix S = MGetIdent();
	Matrix WeaponMatrix = S.SetScale(Vector3(5, 5, 5)) * MGetRotY(200 * DX_PI / 180) * MGetRotZ(30 * DX_PI / 180) * SetModelFramePosition(mModelHandle, "R_HandPinky1", mWeaponHandle);
	MV1SetMatrix(mWeaponHandle, WeaponMatrix);

	if (Input::getInstance().GetKeyDown(KEY_INPUT_Z) || Input::getInstance().GetKeyDown(ButtonCode::PAD_Button1))
	{
		mAnimator.AnimationChange(1, 1, 0.5f);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<PlayerAttack>(mWorld, mWeaponHandle));
	}
	if (mAnimator.IsAnimationEnd())
	{
		mAnimator.AnimationChange(0, 0);
	}

	mAnimator.Update(deltaTime);

}

void Player::onDraw() const
{
	MV1DrawModel(mModelHandle);
	MV1DrawModel(mWeaponHandle);
	//mBody.Translate(mPosition).Draw();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "PlayePosition:x=[%f].y=[%f],z=[%f]", mPosition.x, mPosition.y, mPosition.z);
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
