#include "Player.h"
#include"../../World/IWorld.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"

Player::Player(IWorld& world, Vector3 position):
	Actor(world, "Player", position, {5.0f})
{

}

void Player::onUpdate(float deltaTime)
{
	Vector3 velocity;
	velocity = mRotate.GetForward() * Input::getInstance().GetLeftAnalogStick().y;
	velocity += mRotate.GetLeft() * Input::getInstance().GetLeftAnalogStick().x;
	mRotate *= MGetRotY(Input::getInstance().GetRightAnalogStick().x * 0.01f);
	mPosition += velocity;
}

void Player::onDraw() const
{
}
