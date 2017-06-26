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
	static EffectStorage& getInstance();
	~EffectStorage();
	void HandleRegister(const std::string& fileName, EffectList key);
	int GetHandle(EffectList key);
	void Clear();

private:
	EffectStorage();

private:
	std::map<EffectList, int> mAssets;

};

