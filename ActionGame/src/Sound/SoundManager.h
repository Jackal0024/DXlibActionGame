/*
*サウンドマネージャー
*概要：音声を管理、再生する
*/
#pragma once
#include<string>
#include<map>

class SoundManager
{
public:
	static SoundManager& getInstance();
	void Register(std::string fileName);
	void Play(std::string fileName,bool loop = false);
	void Clear();

private:
	SoundManager();

private:
	std::map<std::string, int> mHandles;
	

};
