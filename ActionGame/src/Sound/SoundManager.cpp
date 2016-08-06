#include "SoundManager.h"
#include<dxlib.h>

SoundManager& SoundManager::getInstance()
{
	static SoundManager sound;
	return sound;
}

void SoundManager::Register(std::string fileName)
{
	auto handle = LoadSoundMem(fileName.c_str());
	mHandles[fileName] = handle;
}

void SoundManager::Play(std::string fileName,bool loop)
{
	 if(loop)PlaySoundMem(mHandles[fileName],DX_PLAYTYPE_LOOP);
	 else PlaySoundMem(mHandles[fileName], DX_PLAYTYPE_BACK);
}

void SoundManager::Clear()
{
	InitSoundMem();
}

SoundManager::SoundManager(){}
