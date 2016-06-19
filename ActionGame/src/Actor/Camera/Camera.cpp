#include "Camera.h"
#include"DxLib.h"
#include"../../Input/Input.h"

Camera::Camera(IWorld & world):
	Actor(world, "Camera", { 0.0f,0.0f,-100.0f }, { {0,0,0},1.0f })
{
	SetCameraNearFar(0.1f, 1000.0f);
	DebugMode = false;
	mYLook = 0;
}

void Camera::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player");
	if (player)
	{
		mYLook += Input::getInstance().GetRightAnalogStick().y * -0.05f;
		mYLook = min(max(mYLook, -3), 3);

		mPosition = player->GetPosition() + Vector3(0.0f,10.0f,0.0f);
		mLook = mPosition + ((player->GetRotate().GetForward() * 3.0f) + Vector3(0,mYLook,0));
	}

	/*if (CheckHitKey(KEY_INPUT_5)) DebugMode = -DebugMode;
	if (DebugMode)
	{
		Vector3 velocity;
		if (CheckHitKey(KEY_INPUT_I))
		{
			velocity += mRotate.GetForward();
		}
		if (CheckHitKey(KEY_INPUT_K))
		{
			velocity -= mRotate.GetForward();
		}
		if (CheckHitKey(KEY_INPUT_J))
		{
			velocity += mRotate.GetLeft();
		}
		if (CheckHitKey(KEY_INPUT_L))
		{
			velocity -= mRotate.GetLeft();
		}
		mPosition += velocity
	}*/
}

void Camera::onDraw() const
{
	SetCameraPositionAndTargetAndUpVec(
		mPosition,
		mLook,
		VGet(0.0f, 1.0f, 0.0f));
}
