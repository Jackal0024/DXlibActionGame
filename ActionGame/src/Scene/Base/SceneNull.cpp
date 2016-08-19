#include "SceneNull.h"
#include"Scene.h"

void SceneNull::Start()
{
}

void SceneNull::Update(float deltaTime)
{
}

void SceneNull::Draw() const
{
}

bool SceneNull::IsEnd() const
{
	return false;
}

Scene SceneNull::Next() const
{
	return Scene::NONE;
}

void SceneNull::End()
{
}
