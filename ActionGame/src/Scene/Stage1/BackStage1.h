/*
*帰りのステージ１
*概要：プレイヤーがステージ２から帰ってきた時のステージ
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class BackStage1 : public IScene
{
public:
	//開始処理
	virtual void Start() override;
	//更新処理
	virtual void Update(float deltaTime) override;
	//描画処理
	virtual void Draw() const override;
	//終了のフラグがたっているか
	virtual bool IsEnd() const override;
	//次のシーン
	virtual Scene Next() const override;
	//終了処理
	virtual void End() override;
	//イベントを受け取る
	void HandleMessage(EventMessage message, void* param);

private:
	//マップを受け取る
	void MapDateInput(const std::string& fileName);
	//モデルを生成する
	void CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate);
	//ゴーレムを設定、生成する
	void GolemCreate(Vector3& position, Vector3& rotate);
	//リザードを設定、生成する
	void LizardCreate(Vector3& position, Vector3& rotate);
	//フェードの処理
	void IsFadeEnd();
private:
	std::shared_ptr<World> mWorld;
	ActorPtr mFade;
	bool isFade;
	Scene mNext;
	MagicMenu mMenu;
	bool isPause;
	bool isEnd;
	bool isDraw;

};
