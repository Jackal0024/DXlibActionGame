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
	//シングルトン
	static EffectStorage& getInstance();
	//デストラクタ
	~EffectStorage();
	//ハンドルを登録
	void HandleRegister(const std::string& fileName, EffectList key);
	//ハンドルを取得
	int GetHandle(EffectList key);
	//全部消す
	void Clear();

private:
	//隠しコンストラクタ
	EffectStorage();

private:
	std::map<EffectList, int> mAssets;

};

