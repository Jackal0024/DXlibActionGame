/*
*�G�t�F�N�g�X�g���[�W�N���X
*�T�v�F�G�t�F�N�g�̃A�Z�b�g���Ǘ��A�ێ�����
*/
#pragma once
#include<string>
#include<map>
#include"AssetList.h"

class EffectStorage
{
public:
	//�V���O���g��
	static EffectStorage& getInstance();
	//�f�X�g���N�^
	~EffectStorage();
	//�n���h����o�^
	void HandleRegister(const std::string& fileName, EffectList key);
	//�n���h�����擾
	int GetHandle(EffectList key);
	//�S������
	void Clear();

private:
	//�B���R���X�g���N�^
	EffectStorage();

private:
	std::map<EffectList, int> mAssets;

};

