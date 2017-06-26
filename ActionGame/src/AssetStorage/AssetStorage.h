/*
*アセットストレージ
*概要：
*/
#pragma once

/*
*アセットストレージ
*概要：登場する３Dアセットを管理しておく
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
