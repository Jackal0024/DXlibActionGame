#include "Camera.h"
#include"DxLib.h"
#include"../../Input/Input.h"

Camera::Camera(IWorld* world):
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
		mYLook += Input::getInstance().GetRightAnalogStick().y* 2 * deltaTime;
		mYLook = min(max(mYLook, -3), 3);

		mPosition = player->GetPosition() + Vector3(0.0f,13.0f,0.0f) + (player->GetRotate().GetForward() * 1.0f);
		mLook = mPosition + ((player->GetRotate().GetForward() * 3.0f) + Vector3(0,mYLook,0));
	}

	mRotate = MGetIdent() * MInverse(GetCameraViewMatrix());
}

void Camera::onDraw() const
{
	SetCameraPositionAndTargetAndUpVec(
		mPosition,
		mLook,
		VGet(0.0f, 1.0f, 0.0f));
}
