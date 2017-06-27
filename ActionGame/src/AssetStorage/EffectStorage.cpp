#include "EffectStorage.h"
#include<dxlib.h>
#include"Effect\Base\EffekseerDxLib.h"

EffectStorage & EffectStorage::getInstance()
{
	static EffectStorage storage;
	return storage;
}

EffectStorage::~EffectStorage()
{
}

void EffectStorage::HandleRegister(const std::string& fileName, EffectList key)
{
	int handle = LoadEffekseerEffect(fileName.c_str());
	mAssets[key] = handle;
}

int EffectStorage::GetHandle(EffectList key)
{
	//if (!mAssets[key]) return -1;
	return mAssets[key];
}

void EffectStorage::Clear()
{
	for (auto itr = mAssets.begin(); itr != mAssets.end(); ++itr) {
		DeleteEffekseerEffect(itr->second);
	}
	mAssets.clear();
}

EffectStorage::EffectStorage()
{
}
