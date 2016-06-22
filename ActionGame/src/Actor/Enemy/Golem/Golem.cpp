#include "Golem.h"

Golem::Golem(IWorld & world, Vector3 position):
	Actor(world, "Golem", position, { {0,10.0f,0},3.0f })
{
	mModel = MV1LoadModel("./res/golem/golem.mv1");
}

void Golem::onStart()
{
	mRotate.SetScale({0.8f,0.8f,0.8f});
	motionid = 0;
	mAnimator.Initialize(mModel, motionid);

}

void Golem::onUpdate(float deltaTime)
{
	if (mAnimator.IsAnimationEnd())
	{
		motionid++;
		if (motionid >= 4) motionid = 0;

	}
	mAnimator.AnimationChange(motionid,0.5f);
	mAnimator.Update(deltaTime);

	/*mPosition += Vector3(0, -0.1, 0);
	auto target = mWorld->FindActor("Player");
	if (target)
	{
		Vector3 velocity = target->GetPosition() - mPosition;
		velocity = VNorm(velocity) * deltatime;
		mPosition += velocity * 0.1f;
	}*/

	mWorld->GetField().Collision(mPosition, mPosition + Vector3(0, 3, 0), mBody.mRadius);
	Vector3 h;
	if (mWorld->GetField().Collision(mPosition + Vector3(0, 10, 0), mPosition + Vector3(0, -30, 0), h))
	{
		mPosition.y = h.y;
	}
	
}

void Golem::onDraw() const
{
	MV1SetMatrix(mModel, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModel);
	mBody.Translate(mPosition).Draw();
}

void Golem::onCollide(Actor & other)
{
	MV1DeleteModel(mModel);
	Dead();
}
