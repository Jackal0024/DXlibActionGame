/*
*フィールドクラス
*概要：フィールドモデルの描画とモデル当たり判定を管理する
*/
#ifndef FIELD_H_
#define FIELD_H_

#include"IField.h"
#include"DxLib.h"
#include"../Math/Vector3.h"

class Field : public IField
{
public:
	//コンストラクタ
	Field(int modelhandle);
	//デストラクタ
	~Field();
	//地面との当たり判定　out_heigtに当たった壁の地点を返す
	bool Collision(const Vector3& start, const Vector3& end, Vector3& out_heigt) const override;
	//当たり判定
	bool Collision(Vector3& start, const Vector3& end, const float& r) override;
	//当たり判定（移動量を考慮）
	bool Collision(Vector3& start, const Vector3& end, const float& r,Vector3& velocity) override;
	//描画処理
	void Draw() const;

private:
};

#endif
