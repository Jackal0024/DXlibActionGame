#include "StateFrame.h"

Frame::Frame(IWorld * world, Vector3 position):
	Actor(world, "Frame", position, Capsule(Vector3(0, 0, 0), 0))
{
	mHandle = LoadGraph("./res/Texture/Frame.png");
}

Frame::~Frame()
{
	DeleteGraph(mHandle);
}

void Frame::onDraw() const
{
	DrawGraph((int)mPosition.x, (int)mPosition.y, mHandle, TRUE);
}
