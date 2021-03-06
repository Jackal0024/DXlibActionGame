#include "WarpCircle.h"
#include"../../Sound/SoundManager.h"

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

WarpCircle::~WarpCircle()
{
	MV1DeleteModel(mHandle);
	MV1DeleteModel(mHandle2);
}

void WarpCircle::onStart()
{
	mTarget = mWorld->FindActor("Player");
}

void WarpCircle::onUpdate(float deltaTime)
{
	if (!mTarget) return;
	Vector3 sub = mTarget->GetPosition() - mPosition;
	sub.y = 0;
	if (VSize(sub) < 10.0f && !isEnd)
	{
		isEnd = true;
		SoundManager::getInstance().Play("./res/Sound/Warp.mp3");
		mWorld->SendMsg(EventMessage::SCENE_END,(void*)&mNext);
	}
	angel += deltaTime;
}

void WarpCircle::onDraw() const
{
	MV1SetMatrix(mHandle, Matrix::CreateRotationY(180) * GetPose());
	MV1DrawModel(mHandle);
	MV1SetMatrix(mHandle2,Matrix::CreateRotationY(angel) * GetPose());
	MV1DrawModel(mHandle2);
	//mBody.Translate(mPosition).Draw();
}

void WarpCircle::onCollide(Actor & other)
{
}

void WarpCircle::onMessage(EventMessage message, void * p)
{
}
