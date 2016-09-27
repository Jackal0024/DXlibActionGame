#include "PlayerAttack.h"
#include"../../Math/Matrix.h"

PlayerAttack::PlayerAttack(IWorld* world, int weapon) :
	Actor(world, "AttackProcess", { MV1GetMatrix(weapon).m[3][0],MV1GetMatrix(weapon).m[3][1],MV1GetMatrix(weapon).m[3][2] }, { Vector3(0,3,0),2 },Tag::PLAYER_ATTACK),
	mWeapoHandle(weapon),
	mTimer(0.0f),
	mAtk(10)
{

}

void PlayerAttack::onUpdate(float deltaTime)
{
	
	Matrix weaponMatrix = MV1GetMatrix(mWeapoHandle);
	mBody.mLine.mStartPos = weaponMatrix.GetPosition();
	mBody.mLine.mEndPos = weaponMatrix.GetPosition() + (weaponMatrix.GetForward() * 3);
	mPosition = weaponMatrix.GetPosition();
	if (mTimer > 0.8f)
	{
		Dead();
	}
	mTimer += deltaTime;
}

void PlayerAttack::onDraw() const
{
	//mBody.Move(mPosition).Draw();
}

void PlayerAttack::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::ENEMY)
	{
		other.HandleMessage(EventMessage::ENEMY_DAMEGE, (void*)&mAtk);
	}
}
