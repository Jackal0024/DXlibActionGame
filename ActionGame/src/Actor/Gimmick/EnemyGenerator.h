/*
*エネミージェネレーター
*概要：エネミーを発生させるファクトリー
*/
#pragma once

#include"../Base/Actor.h"
#include"../Base/ActorPtr.h"
#include<functional>

class EnemyGenerator :public Actor
{
public:
	//アクターを生成する関数を渡す
	EnemyGenerator(IWorld* world, std::function<ActorPtr(void)> func);
	//デストラクタ
	~EnemyGenerator();
private:
	//メッセージを受けとった後の処理
	void onMessage(EventMessage message, void* p);
	//生成する
	void Generator();

private:
	ActorPtr mTarget;
	std::function<ActorPtr(void)> mGeneratorfunc;
};
