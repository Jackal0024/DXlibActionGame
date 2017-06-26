/*
*エフェクトストレージクラス
*概要：エフェクトのアセットを管理、保持する
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

