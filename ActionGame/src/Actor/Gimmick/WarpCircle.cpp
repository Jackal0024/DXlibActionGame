#include "WarpCircle.h"

WarpCircle::WarpCircle(IWorld * world, Vector3 position,Scene next) :
	Actor(world, "Warp", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isEnd(false),
	angel(0),
	mNext(next)
{
	mHandle = MV1LoadModel("./res/WarpCircle/WarpCircle1.mv1");
	mHandle2 = MV1LoadModel("./res/WarpCircle/Aura.mv1");
}

WarpCircle::WarpCircle(IWorld * world, Vector3 position, Vector3 rotate, Scene next):
	Actor(world, "Warp", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isEnd(false),
	angel(0),
	mNext(next)
{
	mHandle = MV1LoadModel("./res/WarpCircle/WarpCircle1.mv1");
	mHandle2 = MV1LoadModel("./res/WarpCircle/Aura.mv1");
}

void WarpCircle::onStart()
{
}

void WarpCircle::onUpdate(float deltaTime)
{
	mTarget = mWorld->FindActor("Player");
	if (!mTarget) return;
	Vector3 sub = mTarget->GetPosition() - mPosition;
	sub.y = 0;
	if (VSize(sub) < 10.0f && !isEnd)
	{
		isEnd = true;
		mWorld->SendMsg(EventMessage::SCENE_END,(void*)&mNext);
	}
	angel += deltaTime;
}

void WarpCircle::onDraw() const
{
	MV1SetMatrix(mHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mHandle);
	MV1SetMatrix(mHandle2, MMult(MGetRotY(angel), GetPose()));
	MV1DrawModel(mHandle2);
	//mBody.Translate(mPosition).Draw();
}

void WarpCircle::onCollide(Actor & other)
{
}

void WarpCircle::onMessage(EventMessage message, void * p)
{
}
