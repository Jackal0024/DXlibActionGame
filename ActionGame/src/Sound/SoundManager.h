/*
*�T�E���h�}�l�[�W���[
*�T�v�F�������Ǘ��A�Đ�����
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
