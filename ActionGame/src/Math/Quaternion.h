/*
*4����
*�T�v�F�N�H�[�^�j�I�����Ǘ�����
*/
#ifndef QUATERNION_H_
#define QUATERNION_H_

class Vector3;
class Matrix;

// �N�H�[�^�j�I��
class Quaternion {
public:
	float x;		// x����
	float y;		// y����
	float z;		// z����
	float w;		// w����

					// �R���X�g���N�^
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	// �R���X�g���N�^
	Quaternion(const Vector3& axis, float angle);

	// ���K������
	static Quaternion Normalize(const Quaternion& q);
	// ���K������
	Quaternion& Normalize();

	// ���ς����߂�
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	// �m���������߂�
	float Length() const;

	// ���ʐ��`���
	static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, float amount);

	// ��]�s�񂩂�N�I�[�^�j�I�����쐬
	static Quaternion CreateFromRotationMatrix(const Matrix& matrix);
};

// �P�����Z�q�I�[�o�[���[�h
Quaternion operator - (const Quaternion& q);

// ������Z�q�I�[�o�[���[�h
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

// �Q�����Z�q�I�[�o�[���[�h
Quaternion operator + (Quaternion q1, const Quaternion& q2);
Quaternion operator - (Quaternion q1, const Quaternion& q2);
Quaternion operator * (Quaternion q1, const Quaternion& q2);
Quaternion operator * (Quaternion q, float s);
Quaternion operator * (float s, Quaternion q);
Quaternion operator / (Quaternion q, float s);

#endif

// end of file
