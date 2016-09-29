#include "Title.h"
#include"../Base/Scene.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include<dxlib.h>
#include<math.h>
#include <stdio.h>
#include"../../Actor/Player/Player.h"
#include"../../System/PlayerStateSave/PlayerSave.h"

void Title::Start()
{
	mRotate = MGetIdent();
	SetBackgroundColor(0, 0, 0);
	mTitleHandle = LoadGraph("./res/Texture/Title/Title.png");
	mTextHandle = LoadGraph("./res/Texture/Title/TitleText.png");
	mTitleModel = MV1LoadModel("./res/Rusted Longsword/LS.x");
	isEnd = false;
	mAlpha = 0;
	mState = State::DEMO;
	mPos = Vector3(0, 100, 0);
	mTimer = 0.0f;
	mRotate.SetScale({ 50,50,50 });
	mRotate = mRotate * Matrix(MGetRotX(-90 * (DX_PI / 180)));

	ChangeLightTypeDir({0,-0.5f,0.5f});
	SetCameraPositionAndTargetAndUpVec(
		{ 0,0,-100 },
		{ 0,0,0 },
		VGet(0.0f, 1.0f, 0.0f));
}

void Title::Update(float deltaTime)
{
	StateUpdate(deltaTime);
}

void Title::Draw() const
{
	MV1SetMatrix(mTitleModel, mRotate);
	//MV1SetPosition(mTitleModel, mPos);
	//MV1SetScale(mTitleModel, { 50,50,50 });
	//MV1SetRotationXYZ(mTitleModel, { -90,0,0 });
	MV1DrawModel(mTitleModel);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DrawGraph(0, 110, mTitleHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (mState == State::WAIT)
	{
		long l = sin(mTimer) * 255 * 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(l));
		DrawGraph(180, 320, mTextHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool Title::IsEnd() const
{
	return isEnd;
}

Scene Title::Next() const
{
	return Scene::GAMEPLAY;
}

void Title::End()
{
}

void Title::StateUpdate(float deltaTime)
{
	mTimer += deltaTime;
	switch (mState)
	{
	case State::DEMO: Demo(deltaTime); break;
	case State::WAIT: Wait(deltaTime); break;
	}
}

void Title::Demo(float deltaTime)
{
	mPos = Vector3::Lerp(Vector3(0, 100, 0), Vector3( 0,-10,0 ), mTimer/2);
	mRotate = Matrix(mRotate).SetPosition(mPos);
	mRotate = mRotate * Matrix(MGetRotY((60 * deltaTime) * (DX_PI / 180)));
	if (mPos.y == -10)
	{
		mAlpha += 1;
		mAlpha = min(mAlpha, 255);
	}
	if (mAlpha >= 255 || Input::getInstance().GetKeyTrigger(KEY_INPUT_SPACE) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button12))
	{
		mState = State::WAIT;
	}
}

void Title::Wait(float deltaTime)
{
	mAlpha = 255;
	mPos = { 0,-10,0 };
	mRotate = Matrix(mRotate).SetPosition(mPos);
	mRotate = mRotate * Matrix(MGetRotY((60 * deltaTime) * (DX_PI / 180)));
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_SPACE) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button12))
	{
		isEnd = true;
	}
}
