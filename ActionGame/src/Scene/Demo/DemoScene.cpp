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

void DemoScene::Start()
{
	isEnd = false;
	mDemoTextYPos = HEIGHT;
	mBackGround = LoadGraph("./res/Texture/Result/EndingBG.png");
	mDemoText = LoadGraph("./res/Texture/Demo/DemoText.png");
}

void DemoScene::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_SPACE) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button10) || mDemoTextYPos <= -856)
	{
		isEnd = true;
	}
	mDemoTextYPos -= deltaTime * 30;
}

void DemoScene::Draw() const
{
	DrawGraph(0, 0, mBackGround, TRUE);
	DrawGraph(0, mDemoTextYPos, mDemoText, TRUE);
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
