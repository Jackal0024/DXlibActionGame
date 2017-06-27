/*
*バウンディングスフィア
*概要：球体の当たり判定クラス
*/
#ifndef BOUNDINGSPHERE_H_
#define BOUNDINGSPHERE_H_

#include"Vector3.h"
#include"Matrix.h"

class BoundingSphere
{
public:
	//コンストラクタ
	BoundingSphere(const Vector3& center, float radius);
	//デフォルトコンストラクタ
	BoundingSphere(float radius = 0.0f);
	//移動処理
	BoundingSphere Translate(const Vector3& position) const;
	//回転移動処理
	BoundingSphere Transform(const Matrix& matrix)const;
	//当たり判定
	bool Intersects(const BoundingSphere& other) const;
	//デバッグ表示
	void Draw() const;

private:
	//球体同士の当たり判定
	bool CollisionSphereAndSphere(Vector3 v1, float r1, Vector3 v2, float r2) const;

private:
	Vector3 mCenter;
	float mRadius;

};

#endif