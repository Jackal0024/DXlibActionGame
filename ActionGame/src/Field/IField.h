/*
*�t�B�[���h��{�N���X
*�T�v�F�t�B�[���h�Ɍp��������N���X
*/
#ifndef IFIELD_H_
#define IFIELD_H_

class Vector3;

class IField
{
public:
	//�f�X�g���N�^
	virtual ~IField() {}
	//�t�B�[���h�̓����蔻��̏������z�֐�
	virtual bool Collision(const Vector3& start, const Vector3& end,Vector3& out_heigt) const = 0;
	//�t�B�[���h�̓����蔻��̏������z�֐�
	virtual bool Collision(Vector3& start, const Vector3& end,const float& r) = 0;
	//�t�B�[���h�̓����蔻��̏������z�֐�
	virtual bool Collision(Vector3& start, const Vector3& end, const float& r,Vector3& velocity) = 0;
protected:
	int mModelHandle;
};

#endif
