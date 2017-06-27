/*
*帰りのステージ２
*概要：プレイヤーが３面から２面に戻ってきた時のステージ
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class BackStage2 : public IScene
{
public:
	//開始処理
	virtual void Start() override;
	//更新処理
	virtual void Update(float deltaTime) override;
	//描画処理
	virtual void Draw() const override;
	//シーンが終了しているフラグが立っているか
	virtual bool IsEnd() const override;
	//次のシーン
	virtual Scene Next() const override;
	//終了処理
	virtual void End() override;
	//イベントを受け取る
	void HandleMessage(EventMessage message, void* param);

private:
	//マップのデータを受け取る
	void MapDateInput(const std::string& fileName);
	//モデルを生成する
	void CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate);

	//ゴーレムを生成
	void GolemCreate(Vector3& position, Vector3& rotate);
	//リザードを生成
	void LizardCreate(Vector3& position, Vector3& rotate);
	//アイスゴーレムを生成
	void IceGolemCreate(Vector3& position, Vector3& rotate);
	//ロックゴーレムを生成
	void RockGolemCreate(Vector3& position, Vector3& rotate);
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
