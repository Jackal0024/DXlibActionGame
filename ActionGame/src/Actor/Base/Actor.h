/*
*�A�N�^�[�N���X
*�T�v�F�Q�[���̊�b�I�u�W�F�N�g�̐e�ɂȂ�N���X
*/

#ifndef ACTOR_H_
#define ACTOR_H_

#include<string>
#include"../../Math/Vector3.h"
#include"../../Math/Matrix.h"
#include"ActorPtr.h"
#include<functional>
#include<algorithm>
#include<forward_list>
#include"../../World/IWorld.h"
#include"../../Math/BoundingSphere.h"
#include"../../Math/Capsule.h"
#include"EventMessage.h"
#include"Tag.h"

class Actor
{
public:
	//�R���X�g���N�^
	Actor(IWorld* world, const std::string& name,const Vector3& position, const Capsule& body,Tag tag = Tag::UNTAGGET);
	//�R���X�g���N�^�i���[�e�[�V������ǉ��j
	Actor(IWorld* world, const std::string& name, const Vector3& position,const Vector3& rotate, const Capsule& body,Tag tag = Tag::UNTAGGET);
	//�_�~�[�R���X�g���N�^
	Actor();

	//�X�^�[�g����
	void Start();
	//�X�V����
	void Update(float deltaTime);
	//�`�揈��
	void Draw() const;
	//�����蔻�菈��
	void Collide(Actor& other);

	//�A�N�^�[�������̎q�ɒǉ�
	ActorPtr AddChild(const ActorPtr& child);
	//�����̎q����T��
	void EachChildren(std::function<void(Actor&)> fn);
	//�����̎q����T���iconst�j
	void EachChildren(std::function<void(Actor&)> fn) const;
	//�q������
	void RemoveChildren(std::function <bool(Actor& actor)> fn);
	//�f�X�t���O���������q��������
	void RemoveChildren();
	//�q�����������蔻��
	void CollideChildren(Actor& other);
	//�Z��̂����蔻��
	void CollideSibling();

	//���S���Ă��邩�H
	bool isDead() const;
	//���S������
	void Dead();
	//�����̖��O��Ԃ�
	const std::string& GetName() const;
	//�����̃|�W�V������Ԃ�
	Vector3 GetPosition() const;
	//�����̉�]�s���Ԃ�
	Matrix GetRotate() const;
	//�����̃��[���h�s���Ԃ�
	Matrix GetPose() const;
	//�����̃^�O��Ԃ�
	Tag GetTag() const;

	//�q����S������
	void ClearChildren();
	//���O����q����T��
	ActorPtr FindChildren(const std::string& name);
	//�֐��Ŏq���������X
	ActorPtr FindChildren(std::function<bool(const Actor&)> fn);

	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:

	//���b�Z�[�W�������Ă������̏���
	virtual void onMessage(EventMessage message, void* param);
	//�J�n����
	virtual void onStart();
	//�X�V����
	virtual void onUpdate(float deltaTime);
	//�`�揈��
	virtual void onDraw() const;
	//�����蔻�菈��
	virtual void onCollide(Actor& other);
	//�������Ă��邩�ǂ���
	bool isCollide(const Actor& other) const;
	//�����蔻�肪���邩�ǂ����H
	bool canCollide(const Actor& other) const;

protected:
	IWorld* mWorld;
	std::string mName;
	Tag mTag;
	Vector3 mPosition;
	Matrix mRotate;
	Capsule	mBody;
	bool mDead;

protected:
	std::forward_list<ActorPtr> mChildren;

};

#endif