/*
*ヒールサークルクラス
*概要：プレイヤーを回復させるクラス
*/
#pragma once

#include"../Base/Actor.h"

class HealCircle :public Actor
{
public:
	//コンストラクタ
	HealCircle(IWorld* world, Vector3 position);
	//コンストラクタ
	HealCircle(IWorld* world, Vector3 position, Vector3 rotate);
	//デストラクタ
	~HealCircle();
private:
	//開始処理
	void onStart() override;
	//描画処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& other) override;
	//イベントを受け取った時の処理
	void onMessage(EventMessage message, void* p);

private:
	int mHandle;
	bool isHealing;
	ActorPtr mTarget;

};
