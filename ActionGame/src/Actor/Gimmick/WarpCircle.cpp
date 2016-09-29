#include "WarpCircle.h"

WarpCircle::WarpCircle(IWorld * world, Vector3 position):
	Actor(world, "Warp", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isEnd(false)
{
	mHandle = MV1LoadModel("./res/WarpCircle/WarpCircle1.mv1");
}

WarpCircle::WarpCircle(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Warp", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isEnd(false)
{
	mHandle = MV1LoadModel("./res/WarpCircle/WarpCircle1.mv1");
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
		//mWorld->AddActor(ActorGroup::UI, std::make_shared<TextDraw>(mWorld, "‰ñ•œ‚µ‚½"));
		mWorld->SendMsg(EventMessage::SCENE_END);
	}
}

void WarpCircle::onDraw() const
{
	MV1SetMatrix(mHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mHandle);
	//mBody.Translate(mPosition).Draw();
}

void WarpCircle::onCollide(Actor & other)
{
}

void WarpCircle::onMessage(EventMessage message, void * p)
{
}
