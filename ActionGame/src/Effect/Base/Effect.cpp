#include "Effect.h"

//なにもしないコンストラクタ
IEffect::IEffect():
	mPlayEffect(-1),
	mEffectHandle(-1)
{
}

//エフェクトを登録する
IEffect::IEffect(const int handle):
	mPlayEffect(-1),
	mEffectHandle(handle)
{
}

IEffect::~IEffect()
{
	DeleteEffekseerEffect(mPlayEffect);
}

//エフェクトを開始する
void IEffect::Play()
{
	mPlayEffect = PlayEffekseerEffect(mEffectHandle);
}

//エフェクトを止める
void IEffect::Stop()
{
	StopPlayingEffeckseerEffect(mPlayEffect);
}

//位置をセットする
void IEffect::SetPosition(Vector3 position)
{
	//プレイしているエフェクトが見つからないなら
	if (mPlayEffect == -1) return;
	SetPosPlayingEffeckseerEffect(mPlayEffect, position.x, position.y, position.z);
}
