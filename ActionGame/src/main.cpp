#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"
#include"Effect\Base\EffekseerDxLib.h"

#pragma comment(linker, "/entry:mainCRTStartup")

int main() {

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

	//DX���C�u�����̏�����
	DxLib_Init();

	//�G�t�F�N�V�[���̏�����
	Effkseer_Init(2048, 2048, 32);

	//�o�b�N�O���E���h�J���[
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();


	//�X�V����
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer(60 * deltatime);;

		Effekseer_Sync3DSetting();

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer();

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
	Effkseer_End();
	DxLib_End();
	return 0;
}