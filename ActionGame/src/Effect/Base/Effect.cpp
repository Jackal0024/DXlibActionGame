#include "Effect.h"

//�Ȃɂ����Ȃ��R���X�g���N�^
IEffect::IEffect():
	mPlayEffect(-1),
	mEffectHandle(-1)
{
}

//�G�t�F�N�g��o�^����
IEffect::IEffect(const int handle):
	mPlayEffect(-1),
	mEffectHandle(handle)
{
}

IEffect::~IEffect()
{
	DeleteEffekseerEffect(mPlayEffect);
}

//�G�t�F�N�g���J�n����
void IEffect::Play()
{
	mPlayEffect = PlayEffekseer3DEffect(mEffectHandle);
}

//�G�t�F�N�g���~�߂�
void IEffect::Stop()
{
	GetEffekseer3DManager()->StopEffect(mPlayEffect);
}

//�ʒu���Z�b�g����
void IEffect::SetPosition(Vector3 position)
{
	//�v���C���Ă���G�t�F�N�g��������Ȃ��Ȃ�
	if (mPlayEffect == -1) return;
	SetPosPlayingEffekseer3DEffect(mPlayEffect, position.x, position.y, position.z);
}
