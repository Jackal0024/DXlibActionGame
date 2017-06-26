/*
*�V�[���̊�{�N���X
*�T�v�F�S�ẴV�[���Ɍp��������N���X
*/
#pragma once

enum  class Scene;

class IScene
{
public:
	virtual ~IScene() {}
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	virtual bool IsEnd() const = 0;
	virtual Scene Next() const = 0;
	virtual void End() = 0;
};
