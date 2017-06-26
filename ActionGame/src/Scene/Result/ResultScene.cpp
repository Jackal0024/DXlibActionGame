#include "ResultScene.h"
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
#include"../../Sound/SoundManager.h"

void ResultScene::Start()
{
	mTimer = 0.0f;
	isEnd = false;

	isDrawRank = false;
	isDrawName = false;
	isDrawStamp = false;;

	mMagicCount = PlayerSave::getInstance().Load().List.size();

	RankCheck(mMagicCount);
	mBackGround = LoadGraph("./res/Texture/Result/EndingBG.png");
	mResultText = LoadGraph("./res/Texture/Result/resultText.png");
	mMagicCountText = LoadGraph("./res/Texture/Result/MagicCountText.png");
	mHilyoukaText = LoadGraph("./res/Texture/Result/hiyoukaText.png");
	mAnataText = LoadGraph("./res/Texture/Result/anata.png");
	mTositeTexr = LoadGraph("./res/Texture/Result/tosite.png");
	mStampTexture = LoadGraph("./res/Texture/Result/certification.png");
	mPressStart = LoadGraph("./res/Texture/Result/PressStart.png");
	mNum = NumberTexture("./res/Texture/Result/num.png", 10, 10, 1, 42, 69);

	PlayMusic("./res/Sound/ResultBGM.ogg", DX_PLAYTYPE_LOOP);
}

void ResultScene::Update(float deltaTime)
{
	mTimer += deltaTime;
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_SPACE) || Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button10))
	{
		isEnd = true;
	}


	if (mTimer >= 2)
	{
		if (!isDrawRank)
		{
			SoundManager::getInstance().Play("./res/Sound/ResultEffect.mp3");
			isDrawRank = true;
		}
	}
	if (mTimer >= 3)
	{
		if (!isDrawName)
		{
			SoundManager::getInstance().Play("./res/Sound/ResultEffect.mp3");
			isDrawName = true;
		}
	}

	if (mTimer >= 5)
	{
		if (!isDrawStamp)
		{
			SoundManager::getInstance().Play("./res/Sound/ResultEffect.mp3");
			isDrawStamp = true;
		}
	}
}

void ResultScene::Draw() const
{
	DrawGraph(0,0, mBackGround, TRUE);
	DrawGraph(0,0, mResultText, TRUE);
	DrawGraph((WIDTH / 2)-187-100,50, mMagicCountText, TRUE);
	mNum.Draw(Vector3((WIDTH / 2) + 100, 35, 0), mMagicCount);

	if (isDrawRank)
	{
		DrawGraph(100, 180, mHilyoukaText, TRUE);
		DrawGraph(200, 300, mRankText, TRUE);
	}
	if (isDrawName)
	{
		DrawGraph(WIDTH - 500, 180, mAnataText, TRUE);
		DrawGraph(WIDTH - 470, 280, mNameText, TRUE);
		DrawGraph(WIDTH - 300, 380, mTositeTexr, TRUE);
	}

	if (isDrawStamp)
	{
		DrawGraph(WIDTH - 300, 300, mStampTexture, TRUE);
	}
	if (mTimer >= 6 && (int)mTimer % 2 == 0)
	{
		DrawGraph((WIDTH / 2) - 268, HEIGHT - 80, mPressStart, TRUE);
	}
}

bool ResultScene::IsEnd() const
{
	return isEnd;
}

Scene ResultScene::Next() const
{
	return Scene::TITLE;
}

void ResultScene::End()
{
	DeleteGraph(mBackGround);
	DeleteGraph(mResultText);
	DeleteGraph(mMagicCountText);
	DeleteGraph(mHilyoukaText);
	DeleteGraph(mAnataText);
	DeleteGraph(mTositeTexr);
	DeleteGraph(mStampTexture);
	DeleteGraph(mRankText);
	DeleteGraph(mNameText);
}

void ResultScene::HandleMessage(EventMessage message, void * param)
{
}

void ResultScene::RankCheck(int rank)
{
	if (rank >= 7)
	{
		mRankText = LoadGraph("./res/Texture/Result/A.png");
		mNameText = LoadGraph("./res/Texture/Result/AText.png");
	}
	else if (rank >= 5)
	{
		mRankText = LoadGraph("./res/Texture/Result/B.png");
		mNameText = LoadGraph("./res/Texture/Result/BText.png");
	}
	else if (rank >= 3)
	{
		mRankText = LoadGraph("./res/Texture/Result/C.png");
		mNameText = LoadGraph("./res/Texture/Result/CText.png");
	}
	else if (rank >= 1)
	{
		mRankText = LoadGraph("./res/Texture/Result/D.png");
		mNameText = LoadGraph("./res/Texture/Result/DText.png");
	}
	else
	{
		mRankText = LoadGraph("./res/Texture/Result/E.png");
		mNameText = LoadGraph("./res/Texture/Result/EText.png");
	}
}
