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
	~EnemyGenerator();
private:
	void onMessage(EventMessage message, void* p);
	void Generator();

private:
	ActorPtr mTarget;
	std::function<ActorPtr(void)> mGeneratorfunc;
};
