#include "AssetStorage.h"
#include<dxlib.h>

AssetStorage & AssetStorage::getInstance()
{
	static AssetStorage sound;
	return sound;
}

AssetStorage::~AssetStorage()
{
}

void AssetStorage::HandleRegister(std::string fileName, std::string key)
{
	int handle = MV1LoadModel(fileName.c_str());
	mAssets[key] = handle;
}

int AssetStorage::GetHandle(std::string key)
{
	if (!mAssets[key]) return -1;
	return mAssets[key];
}

void AssetStorage::Clear()
{
	mAssets.clear();
}

AssetStorage::AssetStorage(){}
