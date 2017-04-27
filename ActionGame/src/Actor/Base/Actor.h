#ifndef ACTOR_H_
#define ACTOR_H_

#include<string>
#include"../../Math/Vector3.h"
#include"../../Math/Matrix.h"
#include"ActorPtr.h"
#include<functional>
#include<algorithm>
#include<forward_list>
#include"../../World/IWorld.h"
#include"../../Math/BoundingSphere.h"
#include"../../Math/Capsule.h"
#include"EventMessage.h"
#include"Tag.h"

class Actor
{
public:
	Actor(IWorld* world, const std::string& name,const Vector3& position, const Capsule& body,Tag tag = Tag::UNTAGGET);
	Actor(IWorld* world, const std::string& name, const Vector3& position,const Vector3& rotate, const Capsule& body,Tag tag = Tag::UNTAGGET);
	Actor();

	void Start();
	void Update(float deltaTime);
	void Draw() const;
	void Collide(Actor& other);

	ActorPtr AddChild(const ActorPtr& child);
	void EachChildren(std::function<void(Actor&)> fn);
	void EachChildren(std::function<void(Actor&)> fn) const;
	void RemoveChildren(std::function <bool(Actor& actor)> fn);
	void RemoveChildren();
	void CollideChildren(Actor& other);
	void CollideSibling();

	bool isDead() const;
	void Dead();
	const std::string& GetName() const;
	Vector3 GetPosition() const;
	Matrix GetRotate() const;
	Matrix GetPose() const;
	Tag GetTag() const;

	void ClearChildren();
	ActorPtr FindChildren(const std::string& name);
	ActorPtr FindChildren(std::function<bool(const Actor&)> fn);

	void HandleMessage(EventMessage message, void* param);

	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:

	virtual void onMessage(EventMessage message, void* param);
	virtual void onStart();
	virtual void onUpdate(float deltaTime);
	virtual void onDraw() const;
	virtual void onCollide(Actor& other);
	bool isCollide(const Actor& other) const;

protected:
	IWorld* mWorld;
	std::string mName;
	Tag mTag;
	Vector3 mPosition;
	Matrix mRotate;
	Capsule	mBody;
	bool mDead;

protected:
	std::forward_list<ActorPtr> mChildren;

};

#endif