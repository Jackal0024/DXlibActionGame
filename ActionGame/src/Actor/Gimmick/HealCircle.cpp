#include "HealCircle.h"
#include"../UI/TextDraw.h"
#include"../UI/FlashEffect.h"
#include"../../Sound/SoundManager.h"

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

HealCircle::~HealCircle()
{
	MV1DeleteModel(mHandle);
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
		mWorld->AddActor(ActorGroup::TOPUI, std::make_shared<FlashEffect>(mWorld, 125, 0.3f, GetColor(0, 255, 65)));
		SoundManager::getInstance().Play("./res/Sound/Healing.mp3");
		mWorld->SendMsg(EventMessage::PLAYER_HEALING);
	}
	else if(VSize(sub) > 10.0f)
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
