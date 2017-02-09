#pragma once

#include<string>
#include"EffekseerForDXLib.h"
#include"../ActionGame/src/Math/Vector3.h"

class IEffect
{
public:
	//なにもしないコンストラクタ
	IEffect();
	//エフェクトを登録する
	IEffect(const int handle);
	//デストラクタ
	~IEffect();
	//エフェクトを開始する
	void Play();
	void Stop();
	//位置をセットする
	void SetPosition(Vector3 position);
protected:
	int mEffectHandle;
	int mPlayEffect;
	Vector3 mPosition;
};
