#pragma once
#include"DxLib.h"

class Matrix : public MATRIX
{
public:
	Matrix(float m11_, float m12_, float  m13_, float m14_,
		float  m21_, float  m22_, float  m23_, float  m24_, 
		float  m31_, float  m32_, float  m33_, float  m34_, 
		float  m41_, float  m42_, float  m43_, float  m44_
		);
	Matrix(MATRIX m);
	//座標を返す
	VECTOR GetPosition() const;
	//横方向のベクトルを返す
	VECTOR GetLeft() const;
	//前方向のベクトルを返す
	VECTOR GetForward() const;
	//上方向のベクトルを返す
	VECTOR GetUp() const;
	//座標を代入する
	void   SetPosition(VECTOR pos);
	//座標を入れた行列を返す
	MATRIX Translate(VECTOR pos) const;
	//透視変換対応の座標変換
	VECTOR Transform(VECTOR v) const;
	//スケールの取得
	VECTOR GetScale() const;
};