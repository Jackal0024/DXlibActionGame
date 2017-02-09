#include "FireBall.h"
#include"../../Player/Player.h"
#include"../../../Sound/SoundManager.h"
#include"../../../AssetStorage/EffectStorage.h"
#include"../../Base/HitInfo.h"

FireBall::FireBall(IWorld * world, Vector3 position, const Vector3& Velocity,Tag tag,float atk) :
Actor(world, "Fire", position, { Line(position,position + Vector3(0,0,0)),10.0f },tag),
mVelocity(Velocity),
mTimer(0),
mIndex(0),
mAtkPower(atk)
{
	mEffect = IEffect(EffectStorage::getInstance().GetHandle(EffectList::FireBallEffect));
	SoundManager::getInstance().Play("./res/Sound/Fire.mp3");
	LoadDivGraph("./res/Particles/FireTexture2.png", 32, 8, 4, 128, 128, mHandle);
	mEffect.Play();
}

FireBall::~FireBall()
{
	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(mHandle[i]);
	}
}

void FireBall::onUpdate(float deltaTime)
{

	mEffect.SetPosition(mPosition+ Vector3(0,-10,0));
	mIndex = (mIndex + 1) % 32;
	mVelocity = VNorm(mVelocity);
	mPosition += mVelocity * 4;
	if (mTimer > 1 || mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 0, 0), mBody.mRadius))
	{
		mEffect.Stop();
		Dead();
	}
	mTimer += deltaTime;
}

void FireBall::onDraw() const
{
	DrawBillboard3D(mPosition, 0.5f, 0.5f, 32, 0, mHandle[mIndex],TRUE);
}

void FireBall::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		Hitinfo hit = { VNorm(mVelocity),mAtkPower};
		other.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
	}
	if (other.GetTag() == Tag::ENEMY)
	{
		mWorld->SendMsg(EventMessage::PLAYER_MAGICUP);
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&mAtkPower);
	}
	mEffect.Stop();
	Dead();
}