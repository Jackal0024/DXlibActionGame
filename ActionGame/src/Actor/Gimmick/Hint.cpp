#include "Hint.h"
#include"../../System/ConstantList/WindowSize.h"

Hint::Hint(IWorld * world, std::string num, Vector3 & position):
	Actor(world, "Hint", position, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isDraw(false)
{
	mModelHandle = MV1LoadModel("./res/Hint/Hint.mv1");
	auto str = "./res/Texture/Hint/" + num + ".png";
	mHintTexture = LoadGraph(str.c_str());

	mTarget = mWorld->FindActor("Player");
}

Hint::Hint(IWorld * world, std::string num,Vector3 position, Vector3 rotate) :
	Actor(world, "Hint", position, {0,rotate.y,0}, { { 0,0,0 },3.0f }, Tag::UNTAGGET),
	isDraw(false)
{
	mModelHandle = MV1LoadModel("./res/Hint/Hint.mv1");
	auto str = "./res/Texture/Hint/" + num + ".png";
	mHintTexture = LoadGraph(str.c_str());

	mTarget = mWorld->FindActor("Player");
}

Hint::~Hint(){
	MV1DeleteModel(mModelHandle);
	DeleteGraph(mHintTexture);
}

void Hint::onUpdate(float deltaTime)
{
	if (!mTarget) return;
	Vector3 sub = mTarget->GetPosition() - mPosition;
	sub.y = 0;
	if (VSize(sub) < 10.0f && !isDraw)
	{
		isDraw = true;
	}
	else if (VSize(sub) > 10.0f)
	{
		isDraw = false;
	}
}

void Hint::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(180 * DX_PI / 180), GetPose()));
	MV1DrawModel(mModelHandle);
	if (isDraw) DrawGraph((WIDTH / 2) - 299.5f, 100, mHintTexture, TRUE);
	//mBody.Translate(mPosition).Draw();

}

void Hint::onCollide(Actor & other)
{
}

void Hint::onMessage(EventMessage message, void * p)
{
}
