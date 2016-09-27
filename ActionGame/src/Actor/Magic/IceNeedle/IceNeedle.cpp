#include "IceNeedle.h"

IceNeedle::IceNeedle(IWorld * world, Vector3 position, Vector3 velocity, int num):
	Actor(world, "Attack",position - Vector3(0,30,0), { Vector3(0,15,0),5 }),
	mVelocity(velocity),
	mNum(num),
	mLifeTimer_(1),
	mDestination(position),
	isNext(false),
	mAtkPower(10)
{
	mModelHandle = MV1LoadModel("./res/IceNeedle/IceNeedle.mv1");
}

void IceNeedle::onUpdate(float deltaTime)
{
	mNum--;
	mLifeTimer_ -= deltaTime;
	mPosition = Vector3::Lerp(mPosition, mDestination, 0.05);
	if (mLifeTimer_ <= 0)
	{
		Dead();
	}
	if (mNum > 0 && !isNext)
	{
		mVelocity.y = 0;
		Vector3 nextPos = mDestination + (mVelocity * 20);
		mWorld->AddActor(ActorGroup::PLAYERATTACK, std::make_shared<IceNeedle>(mWorld,nextPos, mVelocity, mNum));
		isNext = true;
	}

	Vector3 h;
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}
}

void IceNeedle::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose().SetScale({0.05f,0.05f,0.05f})));
	MV1DrawModel(mModelHandle);
	//mBody.Move(mPosition).Draw();
}

void IceNeedle::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		other.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&mAtkPower);
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&mAtkPower);
	}
}
