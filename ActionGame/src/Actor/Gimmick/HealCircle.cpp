#include "HealCircle.h"
#include"../UI/TextDraw.h"

HealCircle::HealCircle(IWorld * world, Vector3 position):
	Actor(world, "Heal", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isHealing(false)
{
	mHandle = MV1LoadModel("./res/HealCircle/MagicCircle2.mv1");
}

HealCircle::HealCircle(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Heal", position,rotate,{ { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isHealing(false)
{
	mHandle = MV1LoadModel("./res/HealCircle/MagicCircle2.mv1");
}

void HealCircle::onStart()
{
}

void HealCircle::onUpdate(float deltaTime)
{
	mTarget = mWorld->FindActor("Player");
	if (!mTarget) return;
	Vector3 sub = mTarget->GetPosition() - mPosition;
	sub.y = 0;
	if (VSize(sub) < 10.0f && !isHealing)
	{
		isHealing = true;
		mWorld->AddActor(ActorGroup::UI, std::make_shared<TextDraw>(mWorld, "‰ñ•œ‚µ‚½"));
		mWorld->SendMsg(EventMessage::PLAYER_HEALING);
	}
	else
	{
		isHealing = false;
	}

}

void HealCircle::onDraw() const
{
	MV1SetMatrix(mHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mHandle);
	//mBody.Translate(mPosition).Draw();
}

void HealCircle::onCollide(Actor & other)
{
}

void HealCircle::onMessage(EventMessage message, void * p)
{
}
