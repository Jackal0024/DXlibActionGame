/*
*�C���v�b�g�N���X
*�T�v�F�p�b�g�ƃL�[�{�[�h�̓��͂��Ǘ�
*/
#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include "KeyNum.h"
#include"Math\Vector3.h"

class Input
{
public:
	//�V���O���g��
	static Input& getInstance(void);
	//�f�X�g���N�^
	~Input();
	//�W���C�X�e�B�b�N�p
	bool GetKeyDown(ButtonCode key);
	//�g���K�[����
	bool GetKeyTrigger(ButtonCode key);
	//�L�[�{�[�h�p
	bool GetKeyDown(int key);
	//�L�[�{�[�h�p�̃g���K�[����
	bool GetKeyTrigger(int key);
	//�X�V����
	void Update();
	//�f�o�b�O�p�̏���
	void Debug();
	//���X�e�B�b�N�̓���
	Vector3 GetLeftAnalogStick();
	//�E�X�e�B�b�N�̓���
	Vector3 GetRightAnalogStick();

private:
	Input();
	Vector3 mInputVectorL;
	Vector3 mInputVectorR;

	bool mButton[32];
	bool mKey[256];
	bool mPrveButton[32];
	bool mPrveKey[256];

	Vector3 mInputVectorLPrev;
	Vector3 mInputVectorRPrev;

};

#endif