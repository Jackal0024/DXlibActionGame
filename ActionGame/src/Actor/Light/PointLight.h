#pragma once

#include"../Base/Actor.h"
#include"../../Math/Vector3.h"

class PointLight : public Actor
{
public:
	//�R���X�g���N�^
	PointLight(IWorld* world);
private:
	//�`��
	virtual void onDraw() const override;
	virtual void onUpdate(float deltaTime) override;

private:
	ActorPtr mPlayer;
};