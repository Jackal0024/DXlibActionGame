/*
*ヒントクラス
*概要：近くに寄ると表示されるUIを持つクラス
*/
#pragma once

#include"../Base/Actor.h"

class Hint : public Actor
{
public:
	//コンストラクタ
	Hint(IWorld* world,const std::string& num, Vector3& position);
	//コンストラクタ
	Hint(IWorld* world,const std::string& num, Vector3 position, Vector3 rotate);
	//デストラクタ
	~Hint();

private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& other) override;
	//メッセージを受け取った時の処理
	void onMessage(EventMessage message, void* p) override;
private:
	ActorPtr mTarget;
	float mTimer;
	int mModelHandle;
	int mHintTexture;
	bool isDraw;
};
