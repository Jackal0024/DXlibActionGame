/*
*アクタークラス
*概要：ゲームの基礎オブジェクトの親になるクラス
*/

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
	//コンストラクタ
	Actor(IWorld* world, const std::string& name,const Vector3& position, const Capsule& body,Tag tag = Tag::UNTAGGET);
	//コンストラクタ（ローテーションを追加）
	Actor(IWorld* world, const std::string& name, const Vector3& position,const Vector3& rotate, const Capsule& body,Tag tag = Tag::UNTAGGET);
	//ダミーコンストラクタ
	Actor();

	//スタート処理
	void Start();
	//更新処理
	void Update(float deltaTime);
	//描画処理
	void Draw() const;
	//当たり判定処理
	void Collide(Actor& other);

	//アクターを自分の子に追加
	ActorPtr AddChild(const ActorPtr& child);
	//自分の子供を探す
	void EachChildren(std::function<void(Actor&)> fn);
	//自分の子供を探す（const）
	void EachChildren(std::function<void(Actor&)> fn) const;
	//子を消す
	void RemoveChildren(std::function <bool(Actor& actor)> fn);
	//デスフラグが立った子供を消す
	void RemoveChildren();
	//子供たち当たり判定
	void CollideChildren(Actor& other);
	//兄弟のあたり判定
	void CollideSibling();

	//死亡しているか？
	bool isDead() const;
	//死亡させる
	void Dead();
	//自分の名前を返す
	const std::string& GetName() const;
	//自分のポジションを返す
	Vector3 GetPosition() const;
	//自分の回転行列を返す
	Matrix GetRotate() const;
	//自分のワールド行列を返す
	Matrix GetPose() const;
	//自分のタグを返す
	Tag GetTag() const;

	//子供を全部消す
	void ClearChildren();
	//名前から子供を探す
	ActorPtr FindChildren(const std::string& name);
	//関数で子供をさあス
	ActorPtr FindChildren(std::function<bool(const Actor&)> fn);

	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);

	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:

	//メッセージが送られてきた時の処理
	virtual void onMessage(EventMessage message, void* param);
	//開始処理
	virtual void onStart();
	//更新処理
	virtual void onUpdate(float deltaTime);
	//描画処理
	virtual void onDraw() const;
	//当たり判定処理
	virtual void onCollide(Actor& other);
	//当たっているかどうか
	bool isCollide(const Actor& other) const;
	//当たり判定があるかどうか？
	bool canCollide(const Actor& other) const;

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