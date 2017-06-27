/*
*デモシーンクラス
*概要：世界感説明のシーンのクラス
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class DemoScene : public IScene
{
public:
	//開始処理
	virtual void Start() override;
	//更新処理
	virtual void Update(float deltaTime) override;
	//描画処理
	virtual void Draw() const override;
	//シーンが終了しているかどうか
	virtual bool IsEnd() const override;
	//次のシーン
	virtual Scene Next() const override;
	//終了処理
	virtual void End() override;
	//イベントを受け取る
	void HandleMessage(EventMessage message, void* param);
private:
	int mBackGround;
	int mDemoText;
	int mSkipText;
	float mDemoTextYPos;

	float mTimer;

	bool isEnd;
	bool isDraw;
};