/*
*�A�N�^�[�}�l�[�W���[�N���X
*�T�v�F�A�N�^�[���Ǘ�����N���X
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
	//�R���X�g���N�^
	ActorManager();
	//����������
	void Initialize();
	//�X�V����
	void Update(float deltaTime);
	//�`�揈��
	void Draw() const;
	//�O���[�v�̃A�N�^�[���C���[�̎q�ɃA�N�^�[��ǉ�
	ActorPtr AddActor(ActorGroup group, const ActorPtr& actor);
	//�A�N�^�[��T��
	ActorPtr FindActor(const std::string& name);
	//���b�Z�[�W���󂯎��
	void HandleMessage(EventMessage message, void* param);

	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	//�����蔻���ݒ�
	void Collide();

private:
	Actor mRoot;
	std::unordered_map<ActorGroup, ActorPtr> mActor;

};

#endif