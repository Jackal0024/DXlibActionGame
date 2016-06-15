#include "Camera.h"
#include"DxLib.h"

Camera::Camera(IWorld & world):
	Actor(world, "Camera", { 0.0f,0.0f,-100.0f }, {1.0f})
{
	SetCameraNearFar(0.0f, 1000.0f);
}

void Camera::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player");
	if (player)
	{
		mPosition = player->GetPosition() + Vector3(0.0f,3.0f,0.0f);
		mLook = mPosition + (player->GetRotate().GetForward() * 3.0f);
	}
}

void Camera::onDraw() const
{
	SetCameraPositionAndTargetAndUpVec(
		mPosition,
		mLook,
		VGet(0.0f, 1.0f, 0.0f));
}
