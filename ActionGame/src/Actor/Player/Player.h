#ifndef PLAYER_H_
#define PLAYER_H_

#include"../Base/Actor.h"
#include"../../Animation/Animator.h"
#include"../Magic/Base/MagicList.h"
#include<vector>

struct PlayerStatus
{
	float HP;
	float MaxHP;
	float MP;
	float MaxMP;
	MagicList CurrentMagic;
	std::vector<MagicList> List;
};

class Player : public Actor
{
public:
	enum State
	{
		MOVE,
		ATTACK,
		DAMAGE
	};
public:
	Player(IWorld* world, Vector3 position);
	Player(IWorld* world, Vector3 position,Vector3 rotate);
	~Player();
	float GetHP();
	float GetMaxHp();
	float GetMP();
	float GetMaxMP();
	float GetMagicInterval();
	float GetAtk();
	std::vector<MagicList> GetHaveMagic();

private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
	void onMessage(EventMessage message, void* p) override;

private:
	void StateChange(State state);
	void StateUpdate(float deltaTime);

	void MoveProcess(float deltaTime);
	void AttackProcess(float deltaTime);
	void DamegeProcess(float deltaTime);

	Matrix SetModelFramePosition(int ModelHandle, char *FrameName, int SetModelHandle) const;
	void Hit(float damege);

	void ATKCharge(float deltaTime);
	void MagicCharge(float deltaTime);

	void SetStatus(PlayerStatus status);

	void MagicAttack();

	void PowerUp();
	void MagicUp();

private:
	int mModelHandle;
	int mWeaponHandle;
	State mState;
	Animator mAnimator;
	float mHitPoint;
	float mMagicPoint;
	float mStateTimer;
	Vector3 mVelocity;

	int mPowerEX;
	int mMagicEX;

	int mNextPowerEX;
	int mNextMagicEX;

	float mAtk;
	float mMagicInterval;

	std::vector<MagicList> mMagicList;
	MagicList mCurrentMagic;

private:
	float MAXHP = 100;
	float MAXMP = 100;

};

#endif