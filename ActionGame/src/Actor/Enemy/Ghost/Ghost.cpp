#include "Ghost.h"
#include"GhostAttack.h"
#include"../../Magic/FireBall/FireBall.h"
#include"../../Magic/IceNeedle/IceNeedle.h"

Ghost::Ghost(IWorld * world, Vector3 position) :
	Actor(world, "Golem", position, { { 0,0,0 },3.0f },Tag::ENEMY),
	mState(State::IDLE),
	mY(0),
	mTimer(0),
	mAttackTimer(0)
{
	mModel = MV1LoadModel("./res/Ghost/Ghost.mv1");
}

Ghost::Ghost(IWorld * world, Vector3 position, Vector3 rotate):
	Actor(world, "Golem", position,rotate, { { 0,10,0 },3.0f }, Tag::ENEMY),
	mState(State::IDLE),
	mY(0),
	mTimer(0),
	mAttackTimer(0)
{
	mModel = MV1LoadModel("./res/Ghost/Ghost.mv1");
}

void Ghost::onStart()
{
}

void Ghost::onUpdate(float deltaTime)
{
	StateUpdate(deltaTime);
	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 0, 0), mPosition + Vector3(0, -100, 0), h))
	{
		mPosition.y = h.y + 10 + mY;
	}
}

void Ghost::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	mBody.Translate(mPosition).Draw();
}

void Ghost::onCollide(Actor & other)
{
	if (other.GetName() == "AttackProcess" && mState != State::DAMAGE)
	{
		Dead();
	}
}

void Ghost::onMessage(EventMessage message, void * p)
{
	switch (message)
	{
	case EventMessage::DEAD: Dead(); break;
	}
}

void Ghost::StateUpdate(float deltaTime)
{
	switch (mState)
	{
	case State::IDLE: Idle(deltaTime); break;
	case State::ATTACK: Attack(deltaTime); break;
	case State::DAMAGE: Damage(deltaTime); break;
	case State::DEAD: DeadState(deltaTime); break;
	}
}

void Ghost::Idle(float deltaTime)
{
	mTarget = mWorld->FindActor("Player");
	Vector3 dir = mTarget->GetPosition() - mPosition;
	if (dir.Length() < 100)
	{
		mAttackTimer += deltaTime;
		if (mAttackTimer > 5)
		{
			if (mAttackTimer > 6) StateChange(State::ATTACK);
		}
		else
		{
			mTimer += deltaTime;
			mY = sin(mTimer) * 3;
		}
	}
}

void Ghost::Attack(float deltaTime)
{
	Vector3 velocity = mTarget->GetPosition() - mPosition + Vector3(0, 5, 0);
	velocity = VNorm(velocity);
	mWorld->AddActor(ActorGroup::ENEMYATTACK, std::make_shared<IceNeedle>(mWorld, mPosition,velocity,3,Tag::ENEMY_ATTACK,200));
	//AddChild(std::make_shared<GhostArrack>(mWorld, mPosition, velocity));
	mAttackTimer = 0;
	StateChange(State::IDLE);
}

void Ghost::DeadState(float deltaTime)
{
}

void Ghost::Damage(float deltaTime)
{
}

void Ghost::StateChange(State nextState)
{
	mState = nextState;
}
