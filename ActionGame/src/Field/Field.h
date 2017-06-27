/*
*�t�B�[���h�N���X
*�T�v�F�t�B�[���h���f���̕`��ƃ��f�������蔻����Ǘ�����
*/
#ifndef FIELD_H_
#define FIELD_H_

#include"IField.h"
#include"DxLib.h"
#include"../Math/Vector3.h"

class Field : public IField
{
public:
	//�R���X�g���N�^
	Field(int modelhandle);
	//�f�X�g���N�^
	~Field();
	//�n�ʂƂ̓����蔻��@out_heigt�ɓ��������ǂ̒n�_��Ԃ�
	bool Collision(const Vector3& start, const Vector3& end, Vector3& out_heigt) const override;
	//�����蔻��
	bool Collision(Vector3& start, const Vector3& end, const float& r) override;
	//�����蔻��i�ړ��ʂ��l���j
	bool Collision(Vector3& start, const Vector3& end, const float& r,Vector3& velocity) override;
	//�`�揈��
	void Draw() const;

private:
};

#endif
