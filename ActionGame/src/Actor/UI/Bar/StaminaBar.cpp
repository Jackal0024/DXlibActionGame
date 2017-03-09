#include "StaminaBar.h"
#include"../../Player/Player.h"

StaminaBar::StaminaBar(IWorld * world, Vector3 position) :
	Actor(world, "Stamina", position, Capsule(Vector3(0, 0, 0), 0))
{
}

StaminaBar::~StaminaBar()
{
}

void StaminaBar::onUpdate(float deltaTime)
{
	auto player = mWorld->FindActor("Player").get();
	mStaminaValue = ((Player*)player)->GetStamina();
	mMaxStamina = ((Player*)player)->GetMaxStamina();
	if (mStaminaValue != mPrevStamina)
	{
		mPrevStamina = max(mStaminaValue, mPrevStamina - (30 * deltaTime));

		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mPrevStamina / mMaxStamina) * (mMaxStamina + 25);
		mSlipBar_rb = Vector3(lt.x + l, lt.y + 15, 0);
	}
}

void StaminaBar::onDraw() const
{
	{
		Vector3 lt = Vector3(mPosition.x + 15, mPosition.y + 0, 0);
		float l = (mStaminaValue / mMaxStamina) * (mMaxStamina + 25);
		Vector3 rb = Vector3(lt.x + l, lt.y + 15, 0);

		Vector3 crb = Vector3(lt.x + mMaxStamina + 25, lt.y + 15, 0);
		DrawBox(lt.x, lt.y, crb.x, crb.y, GetColor(0, 0, 155), true);

		DrawBox(lt.x, lt.y, mSlipBar_rb.x, mSlipBar_rb.y, GetColor(128, 128, 0), true);

		DrawBox(lt.x, lt.y, rb.x, rb.y, GetColor(255, 255, 0), true);
	}
}
