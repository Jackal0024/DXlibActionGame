/*
*�G�t�G�F�N�g�N���X
*�T�v�F�G�t�F�N�g���Ǘ�����N���X
*/
#pragma once

#include<string>
#include"EffekseerDXLib.h"
#include"Math/Vector3.h"

class IEffect
{
public:
	//�Ȃɂ����Ȃ��R���X�g���N�^
	IEffect();
	//�G�t�F�N�g��o�^����
	IEffect(const int handle);
	//�f�X�g���N�^
	~IEffect();
	//�G�t�F�N�g���J�n����
	void Play();
	void Stop();
	//�ʒu���Z�b�g����
	void SetPosition(Vector3 position);
protected:
	int mEffectHandle;
	int mPlayEffect;
	Vector3 mPosition;
};
