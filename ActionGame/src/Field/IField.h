#ifndef IFIELD_H_
#define IFIELD_H_

class Vector3;

class IField
{
public:
	virtual ~IField() {}
	virtual bool Collision(const Vector3& start, const Vector3& end,Vector3& out_heigt) const = 0;
	virtual bool Collision(Vector3& start, const Vector3& end,const float& r, Vector3& out_heigt) const = 0;
protected:
	int mModelHandle;
};

#endif
