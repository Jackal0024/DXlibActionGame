#include "FireParts.h"
#include<dxlib.h>

FirePats::FirePats(IWorld* world, Vector3 position):
	Actor(world, "Parts", position, { Line(position,position + Vector3(0,5,0)),0.0f }),
	mTimer(0.0f),
	mAngle(0.0f)
{
	mTexHandle = LoadGraph("./res/Particles/FireTexture1.png");
}

void FirePats::onUpdate(float deltaTime)
{
	mAngle =+ 1.0f;
	mPosition.y += 0.5f;
	mTimer += deltaTime;
	if (mTimer > 0.5f)
	{
		Dead();
	}
}

void FirePats::onDraw() const
{
	DrawBillboard3D(mPosition, 0.5f, 0.5f, 32, mAngle, mTexHandle, TRUE);
}
