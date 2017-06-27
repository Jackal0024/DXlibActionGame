/*
*アクターマネージャークラス
*概要：アクターを管理するクラス
*/
#ifndef ACTORMANAGER_H_
#define ACTORMANAGER_H_

#include"Actor.h"
#include"ActorPtr.h"
#include"ActorGroup.h"
#include<unordered_map>

class ActorManager
{
public:
	//コンストラクタ
	ActorManager();
	//初期化処理
	void Initialize();
	//更新処理
	void Update(float deltaTime);
	//描画処理
	void Draw() const;
	//グループのアクターレイヤーの子にアクターを追加
	ActorPtr AddActor(ActorGroup group, const ActorPtr& actor);
	//アクターを探す
	ActorPtr FindActor(const std::string& name);
	//メッセージを受け取る
	void HandleMessage(EventMessage message, void* param);

	//コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	//当たり判定を設定
	void Collide();

private:
	Actor mRoot;
	std::unordered_map<ActorGroup, ActorPtr> mActor;

};

#endif