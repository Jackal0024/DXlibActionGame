#ifndef FIELD_H_
#define FIELD_H_

#include"IField.h"
#include"DxLib.h"
#include"../Math/Vector3.h"

class Field : public IField
{
public:
	Field(int modelhandle);
	bool Collision(const Vector3& start, const Vector3& end, Vector3& out_heigt) const override;
	bool Collision(Vector3& start, const Vector3& end, const float& r) const override;
	void Draw() const;
};

#endif
