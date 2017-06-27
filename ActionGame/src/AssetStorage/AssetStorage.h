/*
*�A�Z�b�g�X�g���[�W
*�T�v�F�o�ꂷ��RD�A�Z�b�g���Ǘ����Ă���
*/
#pragma once

#include<string>
#include<map>
#include"AssetList.h"

class AssetStorage
{
public:
	//�V���O���g��
	static AssetStorage& getInstance();
	//�f�X�g���N�^
	~AssetStorage();
	//�n���h����o�^
	void HandleRegister(std::string fileName, std::string key);
	//�n���h�����擾
	int GetHandle(std::string key);
	//�S�ď���
	void Clear();

private:
	//�R���X�g���N�^
	AssetStorage();

private:
	std::map<std::string, int> mAssets;

};
