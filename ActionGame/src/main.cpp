#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"
#include"EffekseerForDXLib.h"

#if _DEBUG
int main() 
{
	//�Q�[���{�̂�錾
	Game game;
	//�E�B���h�E���[�h TRUE�Ȃ�E�B���h�E���[�h
	bool isWindow = TRUE;
	//�f���^�^�C��
	float deltatime = 0;
	//�o�ߎ���
	float timer = 0;

	//���O���o�Ȃ��悤��
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(isWindow);
	//�𑜓x�̐ݒ�
	SetGraphMode(WIDTH, HEIGHT, 16);
	//�X�N���[�����[�h�ɕς��Ă��G�t�F�N�g�������Ȃ��悤��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//�s�N�Z�����C�e�B���O�����邩�H
	SetUsePixelLighting(TRUE);
	//Direct3D�̃o�[�W�����w��
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DX���C�u�����̏�����
	DxLib_Init();

	//�G�t�F�N�V�[���̏�����
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//�o�b�N�O���E���h�J���[
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//�X�V����
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Effekseer_Sync3DSetting();
		int Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer3D();;

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer3D();

		//�f�o�b�O�\���@�f���^�^�C���ƌo�ߎ���
		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		//�f�o�b�O�\���@XYZ�\��
		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime =  (float)(GetNowCount() - Time);
		deltatime /= 1000; //1�b=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}

#endif

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//�Q�[���{�̂�錾
	Game game;
	//�E�B���h�E���[�h TRUE�Ȃ�E�B���h�E���[�h
	bool isWindow = TRUE;
	//�f���^�^�C��
	float deltatime = 0;
	//�o�ߎ���
	float timer = 0;

	//���O���o�Ȃ��悤��
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(isWindow);
	//�𑜓x�̐ݒ�
	SetGraphMode(WIDTH, HEIGHT, 16);
	//�X�N���[�����[�h�ɕς��Ă��G�t�F�N�g�������Ȃ��悤��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//�s�N�Z�����C�e�B���O�����邩�H
	SetUsePixelLighting(TRUE);
	//Direct3D�̃o�[�W�����w��
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DX���C�u�����̏�����
	DxLib_Init();

	//�G�t�F�N�V�[���̏�����
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//�o�b�N�O���E���h�J���[
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//�X�V����
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		Effekseer_Sync3DSetting();
		auto Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer3D();;

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer3D();

		//�f�o�b�O�\���@�f���^�^�C���ƌo�ߎ���
		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		//�f�o�b�O�\���@XYZ�\��
		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime = (float)(GetNowCount() - Time);
		deltatime /= 1000; //1�b=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}