#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"
#include"../../Actor/UI/NumberTexture.h"

class ResultScene : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;
	void HandleMessage(EventMessage message, void* param);

private:
	void RankCheck(int rank);

private:
	NumberTexture mNum;
	int mBackGround;
	int mResultText;
	int mMagicCountText;
	int mMagicCount;
	int mHilyoukaText;
	int mRankText;
	int mAnataText;
	int mNameText;
	int mTositeTexr;
	int mStampTexture;
	int mPressStart;

	float mTimer;

	bool isEnd;

	bool isDrawRank;
	bool isDrawName;
	bool isDrawStamp;

};