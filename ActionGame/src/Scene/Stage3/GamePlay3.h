/*
*�X�e�[�W�R�N���X
*�T�v�F�X�e�[�W�R�i�ŏI�ʁj�̃N���X
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class GamePlay3 : public IScene
{
public:
	//�J�n����
	virtual void Start() override;
	//�X�V����
	virtual void Update(float deltaTime) override;
	//�`�揈��
	virtual void Draw() const override;
	//�V�[�����I�����Ă��邩
	virtual bool IsEnd() const override;
	//���̃V�[��
	virtual Scene Next() const override;
	//�I������
	virtual void End() override;
	//�C�x���g���󂯎��
	void HandleMessage(EventMessage message, void* param);

private:
	//�}�b�v�f�[�^���O���t�@�C������擾
	void MapDateInput(const std::string& fileName);
	//���f���𐶐�
	void CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate);
	//�S�[�����𐶐�
	void GolemCreate(Vector3& position, Vector3& rotate);
	//���U�[�h�𐶐�
	void LizardCreate(Vector3& position, Vector3& rotate);
	//�S�u�����𐶐�
	void GoblinCreate(Vector3& position, Vector3& rotate);
	//�}�W�b�N�}�~�[�𐶐�
	void MagicMummyCreate(Vector3& position, Vector3& rotate);
	//�}�~�[�𐶐�
	void MummyCreate(Vector3& position, Vector3& rotate);
	//���߃}�~�[�𐶐�
	void GuardMummyCreate(Vector3& position, Vector3& rotate);
	//�t�F�[�h����
	void IsFadeEnd();
private:
	std::shared_ptr<World> mWorld;
	ActorPtr mFade;
	bool isFade;
	Scene mNext;
	MagicMenu mMenu;
	bool isPause;
	bool isEnd;
	bool isDraw;

};
