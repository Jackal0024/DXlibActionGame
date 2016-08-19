#include "SceneManager.h"
#include"SceneNull.h"

SceneManager::SceneManager() :
	mCurrentScene(std::make_shared<SceneNull>())
{
}

void SceneManager::Initialize()
{
	End();
	mScene.clear();
}

void SceneManager::Update(float deltaTime)
{
	mCurrentScene->Update(deltaTime);
	if (mCurrentScene->IsEnd())
	{
		Change(mCurrentScene->Next());
	}
}

void SceneManager::Draw() const
{
	mCurrentScene->Draw();
}

void SceneManager::End()
{
	mCurrentScene->End();
	mCurrentScene = std::make_shared<SceneNull>();
}

void SceneManager::Add(Scene name, const IScenePtr & scene)
{
	mScene[name] = scene;
}

void SceneManager::Change(Scene name)
{
	End();
	mCurrentScene = mScene[name];
	mCurrentScene->Start();
}
