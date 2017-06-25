#include "DemoScene.h"
#include"../Base/Scene.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include<dxlib.h>
#include<math.h>
#include <stdio.h>
#include"../../Actor/Player/Player.h"
#include"../../System/PlayerStateSave/PlayerSave.h"
#include<vector>
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../System/ConstantList/WindowSize.h"

#include"EffekseerForDXLib.h"

void DemoScene::Start()
{
	isEnd = false;
	mTimer = 0;
	mDemoTextYPos = HEIGHT;
	mBackGround = LoadGraph("./res/Texture/Result/EndingBG.png");
	mDemoText = LoadGraph("./res/Texture/Demo/DemoText.png");
	mSkipText = LoadGraph("./res/Texture/Demo/SkipText.png");

	PlayMusic("./res/Sound/DemoBGM.ogg", DX_PLAYTYPE_LOOP);
}

void DemoScene::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_SPACE) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button10) || mDemoTextYPos <= -856)
	{
		isEnd = true;
	}
	mDemoTextYPos -= deltaTime * 30;
	mTimer += deltaTime;
}

void DemoScene::Draw() const
{
	DrawGraph(0, 0, mBackGround, TRUE);

	float l = abs(sin(mTimer)) * 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)l);
	DrawGraph(WIDTH - 406, 0, mSkipText, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, (int)mDemoTextYPos, mDemoText, TRUE);
}

bool DemoScene::IsEnd() const
{
	return isEnd;
}

Scene DemoScene::Next() const
{
	return Scene::STAGE1;
}

void DemoScene::End()
{
	DeleteGraph(mBackGround);
	DeleteGraph(mDemoText);
	mDemoTextYPos = HEIGHT;
}

void DemoScene::HandleMessage(EventMessage message, void * param)
{
}
