#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Field/Field.h"

Player::Player(IWorld& world, Vector3 position):
	Actor(world, "Player", position, { {0.0f,10.0f,0.0f},1.0f })
{
	mModelHandle = MV1LoadModel("./res/overload/overlord_Arm.mv1");
}

void Player::onStart()
{
	mRotate.SetScale({ 0.8f,0.8f,0.8f });
	mAnimator.Initialize(mModelHandle, 0,true);
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

	mAnimator.Update(deltaTime);
}

void Player::onDraw() const
{
	
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModelHandle);
	//mBody.Translate(mPosition).Draw();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "PlayePosition:x=[%f].y=[%f],z=[%f]", mPosition.x, mPosition.y, mPosition.z);
}
