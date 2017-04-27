#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"
#include"../Math/Vector3.h"
#include"../Math//Matrix.h"
#include"../Math/BoundingSphere.h"
#include"../Actor/Camera/Camera.h"
#include"../Actor/Light/Light.h"
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/Golem/Golem.h"
#include"../Field/Field.h"
#include"../Math/Line.h"
#include"../Actor/UI/PlayerHP.h"
#include"../Actor/UI/PlayerMP.h"
#include"../Sound/SoundManager.h"

#include"../Scene/Base/Scene.h"
#include"../Scene/LoadAsset/LoadAssetScnen.h"
#include"../Scene/Stage1/GamePlay.h"
#include"../Scene/Stage2/GamePlay2.h"
#include"../Scene/Stage1/BackStage1.h"
#include"../Scene/Stage2/BackStage2.h"
#include"../Scene/Stage3/GamePlay3.h"
#include"../Scene/Title/Title.h"
#include"../Scene/Result/ResultScene.h"
#include"../Scene/Demo/DemoScene.h"



Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
	//�V�[�����C�j�V�����C�Y���Ċe�V�[�����}�l�[�W���[�ɒǉ�-------------------------------
	mSceneManager.Initialize();
	mSceneManager.Add(Scene::LOAD, std::make_shared<LoadAssetScnen>());
	mSceneManager.Add(Scene::TITLE, std::make_shared<Title>());
	mSceneManager.Add(Scene::DEMO , std::make_shared<DemoScene>());
	mSceneManager.Add(Scene::STAGE1, std::make_shared<GamePlay>());
	mSceneManager.Add(Scene::STAGE1_BACK, std::make_shared<BackStage1>());
	mSceneManager.Add(Scene::STAGE2, std::make_shared<GamePlay2>());
	mSceneManager.Add(Scene::STAGE2_BACK, std::make_shared<BackStage2>());
	mSceneManager.Add(Scene::STAGE3, std::make_shared<GamePlay3>());
	mSceneManager.Add(Scene::RESULT, std::make_shared<ResultScene>());
	//-------------------------------------------------------------------------------------
	//���[�h�V�[���Ƀ`�F���W
	mSceneManager.Change(Scene::LOAD);
}

void Game::Update(float deltatime)
{
	//�C���v�b�g���X�V���ăg���K�[����
	Input::getInstance().Update();
	//���݂̃V�[�����X�V
	mSceneManager.Update(deltatime);
}

void Game::Draw()
{
	//���݂̃V�[�����X�V
	mSceneManager.Draw();
}

void Game::Finish()
{
}
