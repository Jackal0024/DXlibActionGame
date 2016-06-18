#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Field/Field.h"

Player::Player(IWorld& world, Vector3 position):
	Actor(world, "Player", position, { {0.0f,3.0f,0.0f},1.0f })
{

}

void Player::onUpdate(float deltaTime)
{
	Vector3 velocity;
	velocity = mRotate.GetForward() * Input::getInstance().GetLeftAnalogStick().y * 0.5f;
	velocity += mRotate.GetLeft() * Input::getInstance().GetLeftAnalogStick().x * 0.5f;
	mRotate = MMult(mRotate, MGetRotY(Input::getInstance().GetRightAnalogStick().x * 0.05f));
	mPosition += velocity + Vector3(0,-0.1,0);

	Vector3 h;
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0,3,0), mBody.mRadius, h);
	if (mWorld->GetField().Collision(mPosition + Vector3(0,10,0), mPosition + Vector3(0,-30, 0), h))
	{
		mPosition.y = h.y;
	}
}

void Player::onDraw() const
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "PlayePosition:x=[%f].y=[%f],z=[%f]", mPosition.x, mPosition.y, mPosition.z);
}
