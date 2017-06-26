/*
*�A�Z�b�g�X�g���[�W
*�T�v�F
*/
#pragma once

/*
*�A�Z�b�g�X�g���[�W
*�T�v�F�o�ꂷ��RD�A�Z�b�g���Ǘ����Ă���
*/
#include<string>
#include<map>
#include"AssetList.h"

class AssetStorage
{
public:
	static AssetStorage& getInstance();
	~AssetStorage();
	void HandleRegister(std::string fileName, std::string key);
	int GetHandle(std::string key);
	void Clear();

private:
	AssetStorage();

private:
	std::map<std::string, int> mAssets;

};
