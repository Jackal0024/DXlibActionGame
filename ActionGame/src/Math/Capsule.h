/*
*カプセルクラス
*概要：カプセルの当たり判定クラス
*/
#ifndef CAPSULE_H_
#define CAPSULE_H_

#include"Line.h"
#include"Matrix.h"

class Capsule
{
public:
	//コンストラクタ
	Capsule(const Line& line, const float radius);
	//コンストラクタ長さからカプセルを作る
	Capsule(const Vector3 length,const float radius);
	//デストラクタ
	~Capsule();
	//接触判定
	bool Intersects(const Capsule& other) const;
	//移動処理
	Capsule Move(const Vector3& position) const;
	//移動処理２
	Capsule Translate(const Vector3& position) const;
	//移動回転処理
	Capsule Transform(const Matrix& matrix)const;
	//デバッグ表示
	void Draw() const;

public:
	Line mLine;
	float mRadius;
	bool isAlive;
	
public:
	bool CollisionCapsuleAndCapsule(const Capsule & other) const;

};

#endif
