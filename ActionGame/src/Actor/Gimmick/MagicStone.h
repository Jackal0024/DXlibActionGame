/*
*マジックストーンクラス
*概要：取るとプレイヤーが魔法を習得できる石
*/
#pragma once

#include"../Base/Actor.h"
#include"../Magic/Base/MagicList.h"

class MagicStone : public Actor
{
public:
	MagicStone(IWorld* world,const std::string& name,Vector3& position,MagicList magic);
	~MagicStone();

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void OverLapSearch();
	void Move(float deltaTime);

private:
	ActorPtr mPlayer;
	bool isDraw;
	float mTimer;
	int mModelHandle;
	int mListSize;
	MagicList mMagicName;

};
