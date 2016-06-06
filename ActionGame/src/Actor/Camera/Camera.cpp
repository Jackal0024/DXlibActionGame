#include "Camera.h"
#include"DxLib.h"

Camera::Camera(IWorld & world):
	Actor(world, "Camera", { 0.0f,0.0f,-100.0f }, {1.0f})
{
}

void Camera::onUpdate(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_W)) mPosition.z += 1.0f;
	if (CheckHitKey(KEY_INPUT_S)) mPosition.z -= 1.0f;
}

void Camera::onDraw() const
{
	SetCameraPositionAndTargetAndUpVec(
		mPosition,
		VGet(0.0f, 0.0f, 0.0f),
		VGet(0.0f, 1.0f, 0.0f));
}
