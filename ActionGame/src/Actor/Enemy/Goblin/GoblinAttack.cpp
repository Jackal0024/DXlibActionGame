#include "GoblinAttack.h"
#include"../../Base/HitInfo.h"

GoblinAttack::GoblinAttack(IWorld * world, const Vector3 & position,Vector3 velocity ,float delay, float Atk):
	Actor(world, "GoblinAttack", position, { Vector3(0,2,0),3 }, Tag::ENEMY_ATTACK),
	mTimer(0.0f),
	mAtk(Atk),
	mDelay(delay),
	mVelocity(velocity)
{
}

void GoblinAttack::onUpdate(float deltaTime)
{
	if (mTimer > mDelay + 0.1f) Dead();
	mTimer += deltaTime;
}

void GoblinAttack::onDraw() const
{
	//�f�o�b�N�p�̕\�����i�͏����Ă���
	//mBody.Move(mPosition).Draw();
}

void GoblinAttack::onCollide(Actor & othr)
{
	//�v���C���[���f�B���C���Ԃ𒴂��Ă���
	if (othr.GetTag() == Tag::PLAYER && (mTimer > mDelay))
	{
		Hitinfo hit = {mVelocity,mAtk };
		othr.HandleMessage(EventMessage::PLAYER_DAMEGE, (void*)&hit);
		Dead();
	}
}
