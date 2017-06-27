/*
*�Q�[���N���X
*�T�v�F�S�̂̍X�V��`����Ǘ�����N���X
*/
#ifndef GAME_H_
#define GAME_H_

#include"../World/World.h"
#include"../Scene/Base/SceneManager.h"
//�Q�[���{��
class Game
{
public:
	//�X�V����
	Game();
	//�f�X�g���N�^
	~Game();
	//����������
	void initialize();
	//�X�V
	void Update(float deltatime);
	//�`��
	void Draw();
	//�I������
	void Finish();

private:
	//�V�[���}�l�[�W���[
	SceneManager mSceneManager;

};

#endif