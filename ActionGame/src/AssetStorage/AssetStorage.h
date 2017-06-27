/*
*アセットストレージ
*概要：登場する３Dアセットを管理しておく
*/
#pragma once

#include<string>
#include<map>
#include"AssetList.h"

class AssetStorage
{
public:
	//シングルトン
	static AssetStorage& getInstance();
	//デストラクタ
	~AssetStorage();
	//ハンドルを登録
	void HandleRegister(std::string fileName, std::string key);
	//ハンドルを取得
	int GetHandle(std::string key);
	//全て消去
	void Clear();

private:
	//コンストラクタ
	AssetStorage();

private:
	std::map<std::string, int> mAssets;

};
