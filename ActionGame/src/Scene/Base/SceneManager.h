/*
*シーンマネージャークラス
*概要：シーン全体を管理する
*/
#pragma once

#include"IScenePtr.h"
#include<unordered_map>

enum class Scene;

class SceneManager
{
public:
	SceneManager();
	void Initialize();
	void Update(float deltaTime);
	void Draw() const;
	void End();
	void Add(Scene name, const IScenePtr& scene);
	void Change(Scene name);

	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;

private:
	std::unordered_map<Scene, IScenePtr> mScene;
	IScenePtr mCurrentScene;

};
