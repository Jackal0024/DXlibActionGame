#include "Actor.h"
#include"DxLib.h"

Actor::Actor(IWorld& world,const std::string name, const Vector3 & position, const BoundingSphere & body):
	mWorld(&world),mName(name),mPosition(position),mRotate(MGetIdent()), mBody(body),mDead(false)
{
}

Actor::Actor(const std::string name):
	mWorld(nullptr), mName("none"), mPosition(0.0f,0.0f,0.0f), mRotate(MGetIdent()), mBody(0.0f), mDead(false)
{
}

void Actor::Update(float deltaTime)
{
	onUpdate(deltaTime);
	EachChildren([&](Actor& actor) {actor.Update(deltaTime); });
}

void Actor::Draw() const
{
	onDraw();
	EachChildren([&](Actor& actor) {actor.Draw(); });

}

void Actor::Collide(Actor & other)
{
	if (isCollide(other))
	{
		onCollide(other);
		other.onCollide(*this);
	}
	EachChildren([&](Actor& actor) {actor.Collide(other); });
}

void Actor::AddChild(const ActorPtr & child)
{
	mChildren.push_front(child);
}

void Actor::EachChildren(std::function<void(Actor&)> fn)
{
	std::for_each(mChildren.begin(), mChildren.end(),
		[&](const ActorPtr& actor) {fn(*actor); });
}

void Actor::EachChildren(std::function<void(Actor&)> fn) const
{
	std::for_each(mChildren.begin(), mChildren.end(),
		[&](const ActorPtr& actor) {fn(*actor); });
}

void Actor::RemoveChildren(std::function<bool(Actor&actor)> fn)
{
	mChildren.remove_if([&](const ActorPtr& actor) {return fn(*actor); });
}

void Actor::RemoveChildren()
{
	RemoveChildren([](Actor& actor) {return actor.isDead(); });
	EachChildren([](Actor& actor) {actor.RemoveChildren(); });
}

void Actor::CollideChildren(Actor & other)
{
	EachChildren([&](Actor& my)
		{other.EachChildren([&](Actor& target) {my.Collide(target); }); });
}

void Actor::CollideSibling()
{
	for (auto i = mChildren.begin(); i != mChildren.end(); ++i)
	{
		std::for_each(std::next(i), mChildren.end(), [&](const ActorPtr& actor) {(*i)->Collide(*actor); });
	}
}

bool Actor::isDead() const
{
	return mDead;
}

void Actor::Dead()
{
	mDead = true;
}

const std::string & Actor::GetName() const
{
	return mName;
}

Vector3 Actor::GetPosition() const
{
	return mPosition;
}

Matrix Actor::GetRotate() const
{
	return mRotate;
}

Matrix Actor::GetPose() const
{
	return Matrix(mRotate).SetPosition(mPosition);
}

void Actor::ClearChildren()
{
	mChildren.clear();
}

ActorPtr Actor::FindChildren(const std::string & name)
{
	return FindChildren([&](const Actor& actor) {return actor.GetName() == name; });
}

ActorPtr Actor::FindChildren(std::function<bool(const Actor&)> fn)
{
	//iには見つかった要素が入る
	//find_ifは見つかった場所のイテレータ―を取得する
	//検索に失敗するとend()（リストの末尾の次の要素）を取得する
	auto i = std::find_if(mChildren.begin(), mChildren.end(),
		[&](const ActorPtr& child) {return fn(*child); });
	if (i != mChildren.end()) {
		return *i;//見つかった要素があればそれを返して終了
	}
	//子の持つ子も調べる
	for (auto child : mChildren) {
		auto actor = child->FindChildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

void Actor::onUpdate(float deltaTime)
{
	(void)deltaTime;
}

void Actor::onDraw() const
{
	mBody.Translate(mPosition).Draw();
}

void Actor::onCollide(Actor & other)
{
	(void)other;
	Dead();
}

bool Actor::isCollide(const Actor & other) const
{
	return mBody.Transform(GetPose()).Intersects(other.mBody.Transform(other.GetPose()));
}
