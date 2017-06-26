/*
*�G�l�~�[�W�F�l���[�^�[
*�T�v�F�G�l�~�[�𔭐�������t�@�N�g���[
*/
#pragma once

#include"../Base/Actor.h"
#include"../Base/ActorPtr.h"
#include<functional>

class EnemyGenerator :public Actor
{
public:
	//�A�N�^�[�𐶐�����֐���n��
	EnemyGenerator(IWorld* world, std::function<ActorPtr(void)> func);
	~EnemyGenerator();
private:
	void onMessage(EventMessage message, void* p);
	void Generator();

private:
	ActorPtr mTarget;
	std::function<ActorPtr(void)> mGeneratorfunc;
};
